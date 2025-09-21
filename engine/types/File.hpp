#pragma once

#include "TypeTraits.hpp"
#include "FileContent.hpp"

#include <misc/FileOpenMode.hpp>

#include <utility/Definitions.hpp>


namespace Ruby {
    class File {
    public:
        RUBY_NODISCARD static bool SaveInFile(Path filePath, StringView data, bool overwrite = false);
        RUBY_NODISCARD static bool SaveInFile(Path filePath, const FileContent& data, bool isBinary, bool overwrite = false);

        RUBY_NODISCARD static Opt<FileContent> LoadFromFile(Path filePath, EFileOpenMode mode = EFileOpenMode::READ);

        RUBY_NODISCARD static File OpenFileStatic(Path filePath, EFileOpenMode mode, bool abortOnError = false);

    public:
        File() = default;
        File(Path path, EFileOpenMode mode, bool abortOnError = false);

        RUBY_NODISCARD bool Open(Path path, EFileOpenMode mode, bool abortOnError = false);

        RUBY_NODISCARD bool IsOpened() const;
        RUBY_NODISCARD bool IsEOF() const;
        RUBY_NODISCARD bool OnBegin() const;

        RUBY_NODISCARD size_t Tell() const;

        RUBY_NODISCARD i32 SeekCur(i32 offset);
        RUBY_NODISCARD i32 SeekBegin(i32 offset);
        RUBY_NODISCARD i32 SeekEnd(i32 offset);

        RUBY_NODISCARD bool Write(const FileContent& data) const;
        RUBY_NODISCARD bool Write(StringView data) const;

        RUBY_NODISCARD Opt<FileContent> ReadAll(bool rewindOnEnd = false);
        RUBY_NODISCARD SharedPtr<byte> ReadAsBytes(bool rewindOnEnd = false);

        void Rewind();

        RUBY_NODISCARD u32 GetFileSize() const;
        RUBY_NODISCARD EFileOpenMode GetOpenMode() const;

        ~File();

    private:
        FILE* m_file = nullptr;
        EFileOpenMode m_mode;
        size_t m_fileSize = 0;
    };
}