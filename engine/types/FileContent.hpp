#pragma once

#include "TypeTraits.hpp"

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>

#include <types/Concepts.hpp>
#include <types/CString.hpp>
#include <types/cast/Cast.hpp>



namespace Kiwi {
    enum class EFileContentDataFormat {
        PLAIN_TEXT, BINARY,
    };


    class FileContent {
    public:
        using value_type = raw_byte;

    public:
        FileContent() = default;
        FileContent(EFileContentDataFormat format, const Vector<u32>& bytesStream);
        FileContent(EFileContentDataFormat format, const Vector<u8>& bytesStream);
        FileContent(EFileContentDataFormat format, const u8* bytesStream, size_t bytesSize);
        FileContent(EFileContentDataFormat format, StringView data);

        FileContent(const FileContent& other);
        FileContent(FileContent&& other) noexcept;

    public:
        KIWI_NODISCARD EFileContentDataFormat GetContentFormat() const;

        KIWI_NODISCARD size_t Size() const;

        KIWI_NODISCARD bool IsEmpty() const;

        KIWI_NODISCARD String GetAsString() const;
        
        template<typename TByteType = u8>
            requires Concepts::SameAs<TByteType, u32> || Concepts::SameAs<TByteType, u8>
        KIWI_NODISCARD Vector<TByteType> GetAsBytesStream() const {
            KIWI_ASSERT_BASIC((m_contentByteSize % sizeof(TByteType)) == 0);

            Vector<TByteType> res(m_contentByteSize / sizeof(TByteType));
            CMemoryTools::MemCpy(
                (void*)res.data(),
                (void*)m_content.data(),
                m_contentByteSize
            );

            return res;
        }

    private:
        // TODO: Do we need this?
        friend struct CastTraits<FileContent>;

        EFileContentDataFormat m_format = EFileContentDataFormat::PLAIN_TEXT;

        size_t m_contentByteSize = 0;
        Vector<raw_byte> m_content;
    };


    template<>
    struct CastTraits<FileContent> {
        // Note: this function would **always** return a value, despite it has Opt<...> as the return type
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<String> ToString(const FileContent& fc) {
            return Opt<String>{ fc.GetAsString() };
        }

        // Keep in mind: this function **always** returns a value, despite it has Opt<...> as it's return type
        // So, feel free to use `Opt<T>::value()` without validation checks
        //
        // For more information see `FileContent::GetAsBytesStream<T>()`
        template<typename TByteType>
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<Vector<TByteType>> ToBytesStream(const FileContent& fc) {
            // This function returns Opt<...>, despite original GetAsBytesStream() returns only Vector<...>, because
            // we need to keep common signature for all functions inside CastTraits structure. 
            // The signature like: `KIWI_NODISCARD KIWI_FORCEINLINE static Opt<TRetType> To<...>()`
            return fc.GetAsBytesStream<TByteType>();
        }
    };
}