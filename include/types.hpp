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

    using HuffmanTableType = std::array<std::pair<int, std::vector<Uint8>>, 16>;


}
#endif /* TYPES_HPP */
