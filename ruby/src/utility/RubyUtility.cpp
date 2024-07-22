#include "RubyUtility.hpp"


namespace Ruby {
    RubyString extractTextFromFile(std::string_view path) {
        FILE* file = nullptr;

        if (fopen_s(&file, path.data(), "rb"))
            RUBY_CRITICAL("extractDataFromFile() : failed to open file \"{}\" (fopen_s returns non-zero value)", path);

        fseek(file, 0, SEEK_END);
        auto fsize = ftell(file);
        rewind(file);

        char* buffer = new char[fsize + 1];
        auto bytesRead = fread(buffer, sizeof(char), fsize, file);
        if (bytesRead != fsize)
            RUBY_CRITICAL("extractDataFromFile() : failed to read all necessary bytes from file \"{}\" (bytes read: {}, expected: {})",
                          path, bytesRead, fsize);
        fclose(file);

        buffer[fsize] = '\0';

        return RubyString { buffer };
    }
}