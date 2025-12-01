#pragma once

#include "TypeTraits.hpp"
#include "FileContent.hpp"

#include <misc/FileOpenMode.hpp>

#include <utility/Definitions.hpp>


namespace Kiwi {
    class File {
    public:
        KIWI_NODISCARD static bool SaveInFile(Path filePath, StringView data, bool overwrite = false);
        KIWI_NODISCARD static bool SaveInFile(Path filePath, const FileContent& data, bool isBinary, bool overwrite = false);

        // Note: you should use `EFileOpenMode::READ | EFileOpenMode::BINARY` to read a file(even a plain text file!)
        KIWI_NODISCARD static Opt<FileContent> LoadFromFile(Path filePath, EFileOpenMode mode = EFileOpenMode::READ);

        KIWI_NODISCARD static File OpenFileStatic(Path filePath, EFileOpenMode mode, bool abortOnError = false);

    public:
        File() = default;
        File(Path path, EFileOpenMode mode, bool abortOnError = false);

        KIWI_NODISCARD bool Open(Path path, EFileOpenMode mode, bool abortOnError = false);

        KIWI_NODISCARD bool IsOpened() const;
        KIWI_NODISCARD bool IsEOF() const;
        KIWI_NODISCARD bool OnBegin() const;

        KIWI_NODISCARD size_t Tell() const;

        KIWI_NODISCARD i32 SeekCur(i32 offset) const;
        KIWI_NODISCARD i32 SeekBegin(i32 offset) const;
        KIWI_NODISCARD i32 SeekEnd(i32 offset) const;

        KIWI_NODISCARD bool Write(const FileContent& data) const;
        KIWI_NODISCARD bool Write(StringView data) const;

        KIWI_NODISCARD Opt<FileContent> ReadAll(bool rewindOnEnd = false) const;
        KIWI_NODISCARD SharedPtr<byte> ReadAsBytes(bool rewindOnEnd = false) const;

        void Rewind() const;

        KIWI_NODISCARD u32 GetFileSize() const;
        KIWI_NODISCARD EFileOpenMode GetOpenMode() const;

        ~File();

    private:
        FILE* m_file = nullptr;
        EFileOpenMode m_mode;
        size_t m_fileSize = 0;
    };
}