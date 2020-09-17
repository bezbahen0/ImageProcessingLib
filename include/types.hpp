#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <memory>

namespace imp
{

    using Uint8 = unsigned char;
    using Uint16 = unsigned short;
    /*using U8 = unsigned char;
    using U16 = unsigned short;
    using S8 = signed char;
    using S16 = signed short;
    using S32 = signed int;
    using F32 = float;
    using F64 = double;*/

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

    using HuffmanTableType = std::array<std::pair<int, std::vector<uint8_t>>, 16>;

}
#endif /* TYPES_HPP */
