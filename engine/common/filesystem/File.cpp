#include "File.hpp"

#include <common/meta/TypeTraits.hpp>
#include <common/cast/Cast.hpp>
#include <common/Debug.hpp>


namespace Kiwi {
    Status<Error<EErrorIO>> File::SaveInFile(Path filePath, StringView data, bool overwrite) {
        return File::SaveInFile(
            std::move(filePath),
            FileContent{ EFileContentDataFormat::PLAIN_TEXT, data },
            overwrite
        );
    }

    Status<Error<EErrorIO>> File::SaveInFile(Path filePath, const FileContent& data, bool isBinary, bool overwrite) {
        auto mode = EFileOpenMode::WRITE;
        if (isBinary) {
            mode |= EFileOpenMode::BINARY;
        }
        if (!overwrite) {
            mode |= EFileOpenMode::APPEND;
        }

        if (auto res = OpenFileStatic(std::move(filePath), mode); !res) {
            return Unexpected(res.GetError());
        }
        else {
            return res.GetValue().Write(data);
        }
    }

    Result<FileContent, EErrorIO> File::LoadFromFile(Path filePath, EFileOpenMode mode) {
        if (auto res = OpenFileStatic(std::move(filePath), mode); !res) {
            return res.GetError();
        }
        else {
            return res.GetValue().ReadAll();
        }
    }

    Result<File, EErrorIO> File::OpenFileStatic(Path filePath, EFileOpenMode mode) {
        File r;
        if (auto err = r.Open(std::move(filePath), mode); !err) {
            return err.error();
        }

        return Success(r);
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

    Status<Error<EErrorIO>> File::Write(const FileContent& data) const {
        KIWI_ASSERT_BASIC(m_file != nullptr);

        size_t toWrite = data.Size();
        Vector<u8> bytesStream = data.GetAsBytesStream();

        size_t bytesStreamElementSize = sizeof(typename decltype(bytesStream)::value_type);
        if (fwrite(bytesStream.data(), bytesStreamElementSize, toWrite, m_file) < toWrite) {
            if (ferror(m_file)) {
                return Unexpected(Error<EErrorIO>::FromKind(Cast<EErrorIO>::FromPosixCodes(errno)));
            }

            return Unexpected(Error<EErrorIO>::FromKind(EErrorIO::UNKNOWN));
        }

        return {};
    }

    Status<Error<EErrorIO>> File::Write(StringView data) const {
        return Write(FileContent(EFileContentDataFormat::PLAIN_TEXT, data));
    }

    Status<Error<EErrorIO>> File::Open(Path path, EFileOpenMode mode) {
        auto cStyleFileOpenMode = Cast<EFileOpenMode>::ToCStyleOpenMode(mode);
        if (!cStyleFileOpenMode) {
            return Unexpected(Error{
                .kind = EErrorIO::INVALID_ARGUMENT,
                .desc = "Failed to cast provided EFileOpenMode to C-Style open mode"
            });
        }

        if (auto strString = path.string();
                errno_t err = fopen_s(&m_file, strString.data(), cStyleFileOpenMode.value().ToCString()))
        {
            m_file = nullptr;

            return Unexpected(Error<EErrorIO>::FromKind(Cast<EErrorIO>::FromPosixCodes(err)));
        }

        (void)SeekEnd(0);
        m_fileSize = Tell();
        Rewind();

        return {};
    }

    Result<FileContent, EErrorIO> File::ReadAll(bool rewindOnEnd) const {
        KIWI_ASSERT_BASIC(m_file != nullptr);
        
        auto contentType = ((m_mode & EFileOpenMode::BINARY) == EFileOpenMode::BINARY) ?
            EFileContentDataFormat::BINARY : EFileContentDataFormat::PLAIN_TEXT;

        (void)SeekBegin(0);
        Result fileBytes = ReadAsBytes(rewindOnEnd);
        if (fileBytes) {
            FileContent content(contentType, fileBytes.GetValue().get(), m_fileSize);
            return Success(content);
        }

        return fileBytes.GetError();
    }

    Result<SharedPtr<byte>, EErrorIO> File::ReadAsBytes(bool rewindOnEnd) const {
        KIWI_ASSERT_BASIC(m_file != nullptr);

        byte* buffer = KIWI_NOTHROW_NEW byte[m_fileSize + 1];
        if (!buffer) {
            Success<SharedPtr<byte>>(std::in_place, nullptr);
        }

        auto wasRead = fread(buffer, sizeof(byte), m_fileSize, m_file);
        if (wasRead != m_fileSize) {
            if (ferror(m_file)) {
                return Error<EErrorIO>::FromKind(Cast<EErrorIO>::FromPosixCodes(errno));
            }
            if (feof(m_file)) {
                return Error<EErrorIO>::FromKind(EErrorIO::UNEXPECTED_EOF);
            }

            return Error<EErrorIO>::FromKind(EErrorIO::UNKNOWN);
        }

        buffer[m_fileSize] = '\0';
        if (rewindOnEnd) {
            Rewind();
        }

        return Success(MakeShared<byte>(buffer, [](byte* ptr) {
            delete[] ptr;
        }));
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