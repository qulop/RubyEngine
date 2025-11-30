#pragma once

#include <types/TypeMetaInfo.hpp>
#include <utility/Assert.hpp>


#define RUBY_CREATE_OBJECT(ClassName)                                                           \
    public:                                                                                     \
        using SelfType = ClassName;                                                             \
                                                                                                \
    public:                                                                                     \
        RUBY_NODISCARD static const TypeMetaInfo& GetStaticTypeMetaInfo() {                     \
            static auto selfTypeMetaInfo = RUBY_CREATE_TYPEINFO_FUNC(ClassName);                \
            return selfTypeMetaInfo;                                                            \
        }                                                                                       \
                                                                                                \
        RUBY_NODISCARD static Ruby::Hash64 GetStaticType() {                                    \
            return GetStaticTypeMetaInfo().GetType();                                           \
        }                                                                                       \
                                                                                                \
        RUBY_NODISCARD static const Ruby::String& GetStaticTypeName() {                         \
            return GetStaticTypeMetaInfo().GetTypeName();                                       \
        }                                                                                       \
                                                                                                \
        RUBY_NODISCARD virtual const TypeMetaInfo& GetTypeMetaInfo() const override {           \
            return GetStaticTypeMetaInfo();                                                     \
        }                                                                                       \
                                                                                                \
        RUBY_NODISCARD virtual Ruby::Hash64 GetType() const override {                          \
            return GetStaticType();                                                             \
        }                                                                                       \
                                                                                                \
        RUBY_NODISCARD virtual const Ruby::String& GetTypeName() const override {               \
            return GetStaticTypeName();                                                         \
        }



namespace Ruby {
    RUBY_FORWARD_DECLARATIONS(
        class Application;

        RUBY_ABSTRACT class ASubsystem;
    )


    RUBY_ABSTRACT class AObject {
        using SubsystemHolderType = HashMap<Hash64, SharedPtr<ASubsystem>>;

    public:
        RUBY_NODISCARD virtual const TypeMetaInfo& GetTypeMetaInfo() const = 0;

        RUBY_NODISCARD virtual Hash64 GetType() const = 0;

        RUBY_NODISCARD virtual const String& GetTypeName() const = 0;

    public:
        RUBY_NODISCARD const AObject* GetBasePtr() const;

        template<Concepts::DerivedFrom<ASubsystem> T>
        void RegisterSubsystem(T* subsystem) {
            RegisterSubsystem(BasicCast::HierarchyCast<ASubsystem*>(subsystem));
        }

        template<Concepts::DerivedFrom<ASubsystem> T>
        void DestroySubsystem() {
            DestroySubsystem(T::GetStaticType());
        }


        template<Concepts::DerivedFrom<ASubsystem> T>
        SharedPtr<T> GetSubsystem() {
            SharedPtr<ASubsystem> basePtr = GetSubsystem(T::GetStaticType());

            if constexpr (std::same_as<SharedPtr<ASubsystem>, std::shared_ptr<ASubsystem>>) {
                return std::static_pointer_cast<T>(basePtr);
            }
            else {
                RUBY_ASSERT(false, "You should to adapt this function for engine's custom SharedPtr<T> type!");
                return nullptr;
            }
        }

        void RegisterSubsystem(ASubsystem* subsystem);
        void DestroySubsystem(Hash64 typeHash);
        SharedPtr<ASubsystem> GetSubsystem(Hash64 typeHash);

        virtual ~AObject() = default;

    protected:
        TypeMetaInfo m_typeMetaInfo;

    private:
        friend class Application;

        static SubsystemHolderType* s_subsystems;
    };


    RUBY_ABSTRACT class ASubsystem : public AObject {
        RUBY_CREATE_OBJECT(ASubsystem)

    public:
        virtual void Init() {}
        virtual void DeInit() {}

        ~ASubsystem() override = default;
    };
}