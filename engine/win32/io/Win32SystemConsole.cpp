#include "Win32SystemConsole.hpp"

#include <win32/Win32Utils.hpp>

#include <types/cast/Cast.hpp>
#include <types/cast/StringCasts.hpp>


namespace {
    constexpr size_t READ_BUFFER_SIZE = 1024;
}


namespace Ruby::Platform::Win32 {
    void Win32SystemConsole::Write() {
        Write(StringView("\r\n", 2));
    }

    void Win32SystemConsole::Write(StringView str) {
        HANDLE hnd = getStdHandle(STD_OUTPUT_HANDLE);
        DWORD written = 0;
        WriteConsoleA(hnd, str.data(),
            BasicCast::To<DWORD>(str.size()), &written, nullptr
        );
    }

    void Win32SystemConsole::WriteLine(StringView str) {
        String s(str.data(), str.size());
        Write(s + "\r\n");
    }

    void Win32SystemConsole::Put(char ch) {
        Write(StringView(&ch, 1));
    }

    Opt<String> Win32SystemConsole::ReadString() {
        HANDLE hnd = getStdHandle(STD_INPUT_HANDLE);
        char buffer[READ_BUFFER_SIZE];
        DWORD readCount = 0;

        if (!ReadConsoleA(hnd, buffer, READ_BUFFER_SIZE, &readCount, nullptr)) {
            return nullopt;
        }

        buffer[readCount] = '\0';
        return String(&buffer[0], readCount);
    }

    Opt<i32> Win32SystemConsole::ReadInt32() {
        return Cast<String>::ToIntI32(ReadString().value_or(""));
    }

    Opt<i64> Win32SystemConsole::ReadInt64() {
        return Cast<String>::ToIntI64(ReadString().value_or(""));
    }

    Opt<float> Win32SystemConsole::ReadFloat() {
        return Cast<String>::ToFloat(ReadString().value_or(""));
    }

    Opt<double> Win32SystemConsole::ReadDouble() {
        return Cast<String>::ToDouble(ReadString().value_or(""));
    }

    void Win32SystemConsole::SetCursorPosition(u16 x, u16 y) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {
            BasicCast::To<SHORT>(x),
            BasicCast::To<SHORT>(y)
        });
    }

    void Win32SystemConsole::Clear() {
        HANDLE hnd = getStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        DWORD count = 0;
        DWORD cellCount = 0;

        if (!GetConsoleScreenBufferInfo(hnd, &bufferInfo)) {
            return;
        }

        cellCount = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;

        FillConsoleOutputCharacter(hnd, ' ', cellCount, { 0, 0 }, &count);
        FillConsoleOutputAttribute(hnd, bufferInfo.wAttributes, cellCount, { 0, 0 }, &count);
        SetCursorPosition(0, 0);
    }

    void Win32SystemConsole::Beep(i32 frequency, i32 duration) {
        ::Beep(frequency, duration);
    }

    void Win32SystemConsole::Flush() {
        FlushFileBuffers(GetStdHandle(STD_OUTPUT_HANDLE));
    }

    void Win32SystemConsole::FlushInput() {
        FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
    }
}
