#pragma once

#include <types/TypeMetaInfo.hpp>
#include <utility/Assert.hpp>


#define KIWI_CREATE_OBJECT(ClassName)                                                           \
    public:                                                                                     \
        using SelfType = ClassName;                                                             \
                                                                                                \
    public:                                                                                     \
        KIWI_NODISCARD static const TypeMetaInfo& GetStaticTypeMetaInfo() {                     \
            static auto selfTypeMetaInfo = KIWI_CREATE_TYPEINFO_FUNC(ClassName);                \
            return selfTypeMetaInfo;                                                            \
        }                                                                                       \
                                                                                                \
        KIWI_NODISCARD static Kiwi::Hash64 GetStaticType() {                                    \
            return GetStaticTypeMetaInfo().GetType();                                           \
        }                                                                                       \
                                                                                                \
        KIWI_NODISCARD static const Kiwi::String& GetStaticTypeName() {                         \
            return GetStaticTypeMetaInfo().GetTypeName();                                       \
        }                                                                                       \
                                                                                                \
        KIWI_NODISCARD virtual const TypeMetaInfo& GetTypeMetaInfo() const override {           \
            return GetStaticTypeMetaInfo();                                                     \
        }                                                                                       \
                                                                                                \
        KIWI_NODISCARD virtual Kiwi::Hash64 GetType() const override {                          \
            return GetStaticType();                                                             \
        }                                                                                       \
                                                                                                \
        KIWI_NODISCARD virtual const Kiwi::String& GetTypeName() const override {               \
            return GetStaticTypeName();                                                         \
        }



namespace Kiwi {
    KIWI_FORWARD_DECLARATIONS(
        class Application;

        KIWI_ABSTRACT class ASubsystem;
    )


    KIWI_ABSTRACT class AObject {
        using SubsystemHolderType = HashMap<Hash64, SharedPtr<ASubsystem>>;

    public:
        KIWI_NODISCARD virtual const TypeMetaInfo& GetTypeMetaInfo() const = 0;

        KIWI_NODISCARD virtual Hash64 GetType() const = 0;

        KIWI_NODISCARD virtual const String& GetTypeName() const = 0;

    public:
        KIWI_NODISCARD const AObject* GetBasePtr() const;

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
                KIWI_ASSERT(false, "You should to adapt this function for engine's custom SharedPtr<T> type!");
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


    KIWI_ABSTRACT class ASubsystem : public AObject {
        KIWI_CREATE_OBJECT(ASubsystem)

    public:
        virtual void Init() {}
        virtual void DeInit() {}

        ~ASubsystem() override = default;
    };
}