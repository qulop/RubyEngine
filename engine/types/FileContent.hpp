#pragma once

#include "TypeTraits.hpp"

#include <utility/Definitions.hpp>
#include <types/Concepts.hpp>
#include <types/CString.hpp>
#include <types/Cast.hpp>



namespace Ruby {
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
        RUBY_NODISCARD EFileContentDataFormat GetContentFormat() const;

        RUBY_NODISCARD size_t Size() const;

        RUBY_NODISCARD Opt<String> GetAsString() const;
        
        template<typename TByteType = u8>
            requires Concepts::SameAs<TByteType, u32> || Concepts::SameAs<TByteType, u8>
        RUBY_NODISCARD Vector<TByteType> GetAsBytesStream() const {
            RUBY_ASSERT_BASIC((m_contentByteSize % sizeof(TByteType)) == 0);

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
}