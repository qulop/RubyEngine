#pragma once

#include <types/TypeTraits.hpp>


namespace Ruby::Platform {
    struct Locale {
    public:
        struct LocaleInfo {
            WideString systemLocale;
            WideString systemEncoding;
        };

    public:
        // Will return struct, which contains `system locale` and `system encoding`
        // For more info see `Ruby::Platform::Locale::LocaleInfo`
        static LocaleInfo GetSystemLocaleInfo();
        static Opt<WideString> GetSystemLocale();
        static Opt<WideString> GetSystemEncoding();
    };
}