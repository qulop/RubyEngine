#pragma once

#include <core/LogLevel.hpp>

#include <types/TypeMetaInfo.hpp>

#include <utility/Assert.hpp>

#include <sync/Thread.hpp>


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

/*  Will produce log with method signature which consists of a class name and a class method, separated with '::' sign.
    For example, `KIWI_CTX_LOG(WARNING, "Hello World") can produce such output:
        `ExampleClass::ExampleFunc() : Hello World` */
#define KIWI_CTX_LOG(verb, msg, ...)    \
    CtxLog(__func__, ELogLevel::verb##_LOG, msg __VA_OPT__(,) __VA_ARGS__)

#define KIWI_LOG(verb, msg, ...)        \
    Log(ELogLevel::verb##_LOG, msg __VA_OPT__(,) __VA_ARGS__)


namespace Kiwi {
    KIWI_FORWARD_DECLARATIONS(
        class Application;

        KIWI_ABSTRACT class ASubsystem;
    )


    KIWI_ABSTRACT class AObject {
        using SubsystemHolderType = HashMap<Hash64, SharedPtr<ASubsystem>>;

    public:
        template<Concepts::DerivedFrom<ASubsystem> T>
        KIWI_NODISCARD static bool IsSubsystemPresent() {
            KIWI_ASSERT_BASIC(s_subsystems);

            return s_subsystems->contains(T::GetStaticType());
        }

    public:
        KIWI_NODISCARD virtual const TypeMetaInfo& GetTypeMetaInfo() const = 0;

        KIWI_NODISCARD virtual Hash64 GetType() const = 0;

        KIWI_NODISCARD virtual const String& GetTypeName() const = 0;

        virtual ~AObject() = default;

    protected:
        KIWI_NODISCARD const AObject* GetObjectBase() const;

        template<Concepts::DerivedFrom<ASubsystem> T, typename... Args>
        void RegisterSubsystem(Args&&... args) {
            ASubsystem* subsystem = KIWI_NOTHROW_NEW T(std::forward<Args>(args)...);
            RegisterSubsystem(subsystem);
        }

        template<Concepts::DerivedFrom<ASubsystem> T>
        void RegisterSubsystem(T* subsystem) {
            RegisterSubsystem(BasicCast::HierarchyCast<ASubsystem*>(subsystem));
        }

        void RegisterSubsystem(ASubsystem* subsystem);

        template<Concepts::DerivedFrom<ASubsystem> T>
        void DestroySubsystem() {
            KIWI_ASSERT_BASIC(s_subsystems);
            KIWI_ASSERT(ThisThread::IsMainThread(), "You must call this function only from a main thread");

            auto it = s_subsystems->find(T::GetStaticType());
            if (it == std::ranges::end(*s_subsystems)) {
                return;
            }

            it->second.reset();
        }

        template<Concepts::DerivedFrom<ASubsystem> T>
        SharedPtr<T> GetSubsystem() {
            return GetSubsystemImpl<T>(this);
        }

        template<Concepts::DerivedFrom<ASubsystem> T>
        SharedPtr<T> GetSubsystem() const {
            return GetSubsystemImpl<T>(this);
        }

        template<typename... Args>
        void Log(ELogLevel lvl, std::format_string<Args...> fmt, Args&&... args) {
            LogImpl(lvl, std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        void CtxLog(const char* funcName, ELogLevel lvl, std::format_string<Args...> fmt, Args&&... args) const {
            String fullSigName = std::format("{}::{}()",
                GetTypeName(), funcName
            );

            LogImpl(lvl, std::format("{} : {}",
                fullSigName, std::format(fmt, std::forward<Args>(args)...))
            );
        }

    private:
        template<Concepts::DerivedFrom<ASubsystem> T, typename Self>
        static SharedPtr<T> GetSubsystemImpl(Self* self) {
            KIWI_ASSERT_BASIC(s_subsystems && AObject::IsSubsystemPresent<T>());

            SharedPtr<ASubsystem> baseSubsystemPtr = s_subsystems->at(T::GetStaticType());
            if constexpr (std::same_as<SharedPtr<ASubsystem>, std::shared_ptr<ASubsystem>>) {
                return std::static_pointer_cast<T>(baseSubsystemPtr);
            }
            else {
                KIWI_ASSERT(false, "You should to adapt this function for engine's custom SharedPtr<T> type!");
                return nullptr;
            }
        }

        void LogImpl(ELogLevel lvl, const String& msg) const;

    private:
        friend class Application;


        TypeMetaInfo m_typeMetaInfo;

        static SubsystemHolderType* s_subsystems;
    };


    KIWI_ABSTRACT class ASubsystem : public AObject {
        KIWI_CREATE_OBJECT(ASubsystem)

    public:
        virtual bool Init();
        virtual void DeInit();

        ~ASubsystem() override = default;
    };
}