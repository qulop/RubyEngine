#include <platform/general_api/Locale.hpp>

#include <Windows.h>


namespace Ruby::Platform {
    Locale::LocaleInfo Locale::GetSystemLocaleInfo() {
        return {
            .systemLocale = Locale::GetSystemLocale().value_or(L""),
            .systemEncoding = Locale::GetSystemEncoding().value_or(L"")
        };
    }

    Opt<WideString> Locale::GetSystemLocale() {
        WideString localeStr;
        if (GetUserDefaultLocaleName(localeStr.data(), LOCALE_NAME_MAX_LENGTH) == 0) {
            return nullopt;
        }

        return localeStr;
    }

    Opt<WideString> Locale::GetSystemEncoding() {
        return nullopt;
    }
}