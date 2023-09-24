#pragma once

#include <core/Core.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace Ruby
{

typedef char Byte;
typedef uint16_t PngInt; 
    

#define HEX(num)    std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(num)


struct _PngChunk
{
    Byte length[4];
    Byte chunkType[4];
    Byte chunkContent[4];
    Byte crc[4];

};


class Png
{
public:
    Png(void) noexcept;

    Png(const std::string& path) noexcept;

    // void open(const std::string& path) noexcept;

    void changeOpacity(const float op) const noexcept;

    Byte getColorType(void) noexcept;

    // void close(void) noexcept;

    ~Png(void) noexcept;

private:
    std::fstream pngImage;

};

}