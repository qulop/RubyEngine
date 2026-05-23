#include "Debug.hpp"

#include <common/types/String.hpp>
#include <platform/Platform.hpp>
#include <platform/io/SystemConsole.hpp>


namespace Kiwi {
    void Debug::HandleAssert(StringView expr, StringView errMsg, std::source_location loc) {
        Console::Write("Assertion failed:\n\t-- Expression: {}\n\t-- File: {}\n\t-- Line: {}\n",
            expr,
            loc.file_name(),
            loc.line()
        );

        if(!errMsg.empty()) {
            Console::WriteLine("\t-- Message: {}\n", errMsg);
        }
        else {
            Console::Write();
        }

    #ifdef KIWI_DEBUG_BUILD
        Platform::Breakpoint();
    #endif

        Platform::CriticalShutdown();
    }
};
