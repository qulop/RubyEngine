#include "Png.hpp"


namespace Ruby
{
    Png::Png(void) noexcept
    {

    }

    Png::Png(const std::string& path) noexcept
    {
        pngImage.open(path, std::ios::binary | std::ios::out);
    }

    void Png::changeOpacity(const float op) const noexcept
    {
        RUBY_ASSERT(op >= 0 && op <= 1);
    }

    Byte Png::getColorType(void) noexcept
    {
        if (!pngImage.is_open())
            return -1;
        std::cout << "Ok\n";

        // Byte colorType;
        // for (size_t byteNo = 0; byteNo < 25; byteNo++)
        // {
        //     pngImage.get(colorType);
        //     std::cout << static_cast<int>(colorType) << std::endl;
        // }

        std::vector<Byte> buffer{ 26 }; // Color type contained in 25-th byte in INHR chunk
        pngImage.read(&buffer.at(0), 25);

        return static_cast<PngInt>(buffer.at(25));
        // return colorType;
    }





    Png::~Png(void) noexcept
    {
        pngImage.close();
    }

}