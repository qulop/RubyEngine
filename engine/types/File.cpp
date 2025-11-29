#include "File.hpp"
#include "Logger.hpp"

#include <types/TypeTraits.hpp>
#include <types/cast/Cast.hpp>

#include <utility/Assert.hpp>


namespace Ruby {
    bool File::SaveInFile(Path filePath, StringView data, bool overwrite) {
        return File::SaveInFile(
            std::move(filePath), 
            FileContent{ EFileContentDataFormat::PLAIN_TEXT, data }, 
            overwrite
        );
    }

    bool File::SaveInFile(Path filePath, const FileContent& data, bool isBinary, bool overwrite) {
        auto mode = EFileOpenMode::WRITE;
        if (isBinary) {
            mode |= EFileOpenMode::BINARY;
        }
        if (!overwrite) {
            mode |= EFileOpenMode::APPEND;
        }

        return File::OpenFileStatic(
            std::move(filePath),
            mode
        )
        .Write(data);
    }

    Opt<FileContent> File::LoadFromFile(Path filePath, EFileOpenMode mode) {
        return File::OpenFileStatic(
            std::move(filePath),
            mode
        )
        .ReadAll();
    }

    File File::OpenFileStatic(Path filePath, EFileOpenMode mode, bool abortOnError) {
        return File {
            std::move(filePath),
            mode,
            abortOnError
        };
    }


    File::File(Path path, EFileOpenMode mode, bool abortOnError) {
        if (!Open(std::move(path), mode, abortOnError)) {
            return;
        }

        m_mode = mode;
    }

    bool File::IsOpened() const {
        return m_file != nullptr;
    }

    bool File::IsEOF() const {
        return feof(m_file);
    }

    bool File::OnBegin() const {
        return Tell() == 0;
    }

    size_t File::Tell() const {
        return ftell(m_file);
    }

    i32 File::SeekCur(i32 offset) const {
        return fseek(m_file, offset, SEEK_CUR);
    }

    i32 File::SeekBegin(i32 offset) const {
        return fseek(m_file, offset, SEEK_SET);
    }

    i32 File::SeekEnd(i32 offset) const {
        return fseek(m_file, offset, SEEK_END);
    }

    bool File::Write(const FileContent& data) const {
        RUBY_ASSERT_BASIC(m_file != nullptr);

        size_t toWrite = data.Size();
        Vector<u8> bytesStream = data.GetAsBytesStream();

        size_t bytesStreamElementSize = sizeof(typename decltype(bytesStream)::value_type);
        if (fwrite(bytesStream.data(), bytesStreamElementSize, toWrite, m_file) < toWrite) {
            RUBY_ERROR("File::Write() : Failed to write all symbols in file");
            return false;
        }

        return true;
    }

    bool File::Write(StringView data) const {
        return Write(FileContent(EFileContentDataFormat::PLAIN_TEXT, data));
    }

    bool File::Open(Path path, EFileOpenMode mode, bool abortOnError) {
        auto cstylFileOpenMode = Cast<EFileOpenMode>::ToCStyleOpenMode(mode);
        if (!cstylFileOpenMode) {
            return false;
        }

        if (auto strString = path.string(); fopen_s(&m_file, strString.data(), cstylFileOpenMode.value().c_str())) {
            m_file = nullptr;

            if (abortOnError) {
                RUBY_CRITICAL("File::Open() : Failed to open file \"{}\"", strString.data());
            }

            RUBY_ERROR("File::Open() : Failed to open file \"{}\". abortOnError = false", strString.data());
            return false;
        }

        (void)SeekEnd(0);
        m_fileSize = Tell();
        Rewind();

        return true;
    }

    Opt<FileContent> File::ReadAll(bool rewindOnEnd) const {
        RUBY_ASSERT_BASIC(m_file != nullptr);
        
        auto contentType = ((m_mode & EFileOpenMode::BINARY) == EFileOpenMode::BINARY) ?
            EFileContentDataFormat::BINARY : EFileContentDataFormat::PLAIN_TEXT;

        (void)SeekBegin(0);
        auto fileBytes = ReadAsBytes(rewindOnEnd);
        return (fileBytes) ?
            Opt<FileContent>{ FileContent{ contentType, fileBytes.get(), m_fileSize } } :
            nullopt;
    }

    SharedPtr<byte> File::ReadAsBytes(bool rewindOnEnd) const {
        RUBY_ASSERT_BASIC(m_file != nullptr);

        byte* buffer = new(std::nothrow) byte[m_fileSize + 1];
        if (!buffer) {
            return nullptr;
        }

        auto wasRead = fread(buffer, sizeof(byte), m_fileSize, m_file);
        if (wasRead != m_fileSize) {
            return nullptr;
        }

        buffer[m_fileSize] = '\0';
        if (rewindOnEnd) {
            Rewind();
        }

        return MakeShared<byte>(buffer, [](byte* ptr) {
            delete[] ptr;
        });
    }

    void File::Rewind() const {
        rewind(m_file);
    }

    u32 File::GetFileSize() const {
        return BasicCast::To<u32>(m_fileSize);
    }

    EFileOpenMode File::GetOpenMode() const {
        return m_mode;
    }

    File::~File() {
        fclose(m_file);
    }
}