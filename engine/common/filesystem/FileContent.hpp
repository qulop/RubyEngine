#pragma once

#include <common/meta/TypeTraits.hpp>
#include <common/meta/Concepts.hpp>
#include <common/types/CString.hpp>
#include <common/cast/Cast.hpp>
#include <common/Definitions.hpp>
#include <common/Assert.hpp>



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
        EFileContentDataFormat m_format = EFileContentDataFormat::PLAIN_TEXT;

        size_t m_contentByteSize = 0;
        Vector<raw_byte> m_content;
    };


    template<>
    struct CastTraits<FileContent> {
        KIWI_NODISCARD KIWI_FORCEINLINE static String ToString(const FileContent& fc) {
            return fc.GetAsString();
        }

        template<typename TByteType>
        KIWI_NODISCARD KIWI_FORCEINLINE static Vector<TByteType> ToBytesStream(const FileContent& fc) {
            return fc.GetAsBytesStream<TByteType>();
        }
    };
}