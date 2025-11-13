#pragma once

#include <utility/Definitions.hpp>

#include <types/TypeTraits.hpp>
#include <sync/Mutex.hpp>


namespace Ruby::Platform::Win32 {
    class SystemConsoleWin32 {
    public:
        SystemConsoleWin32() = delete;

    public:
        static void Write();
        static void Write(StringView str);
        static void WriteLine(StringView str);

        template<typename... Args>
        static void Write(std::format_string<Args...> fmt, Args... args) {
            Write(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void WriteLine(std::format_string<Args...> fmt, Args... args) {
            WriteLine(std::format(fmt, std::forward<Args>(args)...));
        }

        static void Put(char ch);

        RUBY_NODISCARD static Opt<String> ReadString();
        RUBY_NODISCARD static Opt<i32> ReadInt32();
        RUBY_NODISCARD static Opt<i64> ReadInt64();
        RUBY_NODISCARD static Opt<float> ReadFloat();
        RUBY_NODISCARD static Opt<double> ReadDouble();

        static void SetCursorPosition(u16 x, u16 y);

        static void Clear();

        static void Beep(i32 frequency, i32 duration);

        static void Flush();
        static void FlushInput();
    };
}