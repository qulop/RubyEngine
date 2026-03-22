#include "SystemConsoleWin32.hpp"

#include <common/cast/Cast.hpp>
#include <common/cast/StringCasts.hpp>
#include <platform/PlatformVars.hpp>

#include "platform/Platform.hpp"


namespace {
    constexpr size_t READ_BUFFER_SIZE = 1024;
}


namespace Kiwi::Platform::Win32 {
    void SystemConsoleWin32::Write() {
        Write(StringView("\r\n", 2));
    }

    void SystemConsoleWin32::Write(StringView str) {
        KIWI_SCOPED_LOCK(Globals::Platform::g_consoleIOMutex);

        HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hnd == NULL || hnd == INVALID_HANDLE_VALUE) {
            return;
        }

        DWORD written = 0;
        WriteConsoleA(hnd, str.data(),
            BasicCast::To<DWORD>(str.size()), &written, nullptr
        );
    }

    void SystemConsoleWin32::WriteLine(StringView str) {
        String s(str.data(), str.size());
        Write(s + "\r\n");
    }

    void SystemConsoleWin32::Put(char ch) {
        Write(StringView(&ch, 1));
    }

    Opt<String> SystemConsoleWin32::ReadString() {
        KIWI_SCOPED_LOCK(Globals::Platform::g_consoleIOMutex);

        HANDLE hnd = GetStdHandle(STD_INPUT_HANDLE);
        if (hnd == NULL || hnd == INVALID_HANDLE_VALUE) {
            return nullopt;
        }

        char buffer[READ_BUFFER_SIZE];
        DWORD readCount = 0;

        if (!ReadConsoleA(hnd, buffer, READ_BUFFER_SIZE, &readCount, nullptr)) {
            return nullopt;
        }

        buffer[readCount] = '\0';
        return String(&buffer[0], readCount);
    }

    Opt<i32> SystemConsoleWin32::ReadInt32() {
        return Cast<String>::ToIntI32(ReadString().value_or(""));
    }

    Opt<i64> SystemConsoleWin32::ReadInt64() {
        return Cast<String>::ToIntI64(ReadString().value_or(""));
    }

    Opt<float> SystemConsoleWin32::ReadFloat() {
        return Cast<String>::ToFloat(ReadString().value_or(""));
    }

    Opt<double> SystemConsoleWin32::ReadDouble() {
        return Cast<String>::ToDouble(ReadString().value_or(""));
    }

    void SystemConsoleWin32::SetCursorPosition(u16 x, u16 y) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {
            BasicCast::To<SHORT>(x),
            BasicCast::To<SHORT>(y)
        });
    }

    void SystemConsoleWin32::Clear() {
        KIWI_SCOPED_LOCK(Globals::Platform::g_consoleIOMutex);

        HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hnd == NULL || hnd == INVALID_HANDLE_VALUE) {
            return;
        }

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

    void SystemConsoleWin32::Beep(i32 frequency, i32 duration) {
        ::Beep(frequency, duration);
    }

    void SystemConsoleWin32::Flush() {
        FlushFileBuffers(GetStdHandle(STD_OUTPUT_HANDLE));
    }

    void SystemConsoleWin32::FlushInput() {
        FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
    }
}
