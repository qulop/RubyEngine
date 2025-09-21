#include "FileContent.hpp"

#include <types/Cast.hpp>
#include <types/CString.hpp>


namespace Ruby {
    FileContent::FileContent(EFileContentDataFormat format, const Vector<u32>& bytesStream) :
        m_format(format),
        m_contentByteSize((bytesStream.size() * sizeof(u32)) / sizeof(raw_byte))
    {
        m_content.resize(m_contentByteSize);
        CMemoryTools::MemCpy(
            (void*)m_content.data(),
            (void*)bytesStream.data(),
            m_contentByteSize
        );
    }

    FileContent::FileContent(EFileContentDataFormat format, const Vector<u8>& bytesStream) :
        m_format(format),
        m_contentByteSize((bytesStream.size() * sizeof(u8)) / sizeof(raw_byte))
    {
        m_content.resize(m_contentByteSize);
        CMemoryTools::MemCpy(
            (void*)m_content.data(),
            (void*)bytesStream.data(),
            m_contentByteSize
        );
    }

    FileContent::FileContent(EFileContentDataFormat format, const u8* bytesStream, size_t bytesSize) :
        m_format(format),
        m_contentByteSize(bytesSize),
        m_content(
            (const raw_byte*)bytesStream,
            (const raw_byte*)(bytesStream + bytesSize)
        )
    {}

    FileContent::FileContent(EFileContentDataFormat format, StringView data) :
        m_format(format),
        m_contentByteSize(data.size()),
        m_content(
            (const raw_byte*)data.data(),
            (const raw_byte*)(data.data() + data.size())
        )
    {}

    FileContent::FileContent(const FileContent& other) :
        m_format(other.m_format),
        m_contentByteSize(other.m_contentByteSize),
        m_content(other.m_content)
    {}

    FileContent::FileContent(FileContent&& other) noexcept :
        m_format(std::exchange(other.m_format, EFileContentDataFormat::PLAIN_TEXT)),
        m_contentByteSize(std::exchange(other.m_contentByteSize, 0)),
        m_content(std::move(other.m_content))
    {}

    EFileContentDataFormat FileContent::GetContentFormat() const {
        return m_format;
    }

    size_t FileContent::Size() const {
        return m_contentByteSize;
    }

    Opt<String> FileContent::GetAsString() const {
        //if (m_format != EFileContentDataFormat::PLAIN_TEXT) {
        //    return nullopt;
        //}

        return String{
            BasicCast::UnsafeCast<const char*>(m_content.data()),
            m_content.size()
        };
    }
}
