#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <memory>

namespace imp
{

    using Int8 = char;
    using Int16 = short;
    using Uint8 = unsigned char;
    using Uint16 = unsigned short;

    struct ImgMeta
    {
        int height;
        int width;
        int channels;
    };

    enum 
    {
        GRAY = 1,
        GRAYA = 2,
        RGB = 3,
        RGBA = 4 
    };

    enum RGBComponents
    {
        RED,
        GREEN,
        BLUE
    };

    struct Size
    {
        int width;
        int height;
        Size() : width(0), height(0)
        {
        }
        Size(int width, int height) : width(width), height(height)
        {
        }
    };

    using HuffmanTableType = std::array<std::pair<int, std::vector<Uint8>>, 16>;
    using Matrix8x8 = std::array<std::array<int, 8>, 8>;
    using CompareMtrices = std::vector<Matrix8x8>;

}
#endif /* TYPES_HPP */
