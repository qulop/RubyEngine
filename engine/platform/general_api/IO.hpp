#pragma once

#include <types/TypeTraits.hpp>
#if defined(RUBY_WIN32_USED)
    #include "Windows.h"    // For HANDLE
#endif


namespace Ruby::Platform {
    // #if defined(RUBY_WIN32_USED)
    //     using fhandler_t = HANDLE;
    // #elif defined(RUBY_LINUX_USED)
    //     using fhandler_t = i32;
    // #else
    //     #error "Unsupported platform: Failed to choose alias for `fhandler_t`!"
    // #endif


    // class FileOut : Details::Streams::_IO_Base<FileOut> {
    // public:
    //     static FileOut OpenStatic(std::wstring_view path);
    //     static FileOut OpenStatic(fhandler_t desc);

    // public:
    //     FileOut(std::wstring_view path);
    //     FileOut(fhandler_t desc);

    // public:
    //     bool IsOpen() const;
    //     bool EndOfFile() const;
    //     bool OnBegin() const;

    //     size_t GetFileSize() const;

    //     size_t Tell() const;
        
    //     void Rewind();

    // public:
    //     ~FileOut();

    // private:
    //     fhandler_t m_handler = NULL;
    // };


    // namespace Globals {
    //     extern OStream stdOut;
    //     extern OStream stdErr;
    //     extern IStream stdIn;
    // }


    void writeInConsole(std::string_view msg, bool isFlush=false);
}   
