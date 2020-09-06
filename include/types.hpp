#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <memory>

namespace imp
{
    /*using U8 = unsigned char;
    using U16 = unsigned short;
    using S8 = signed char;
    using S16 = signed short;
    using S32 = signed int;
    using F32 = float;
    using F64 = double;*/

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


}
#endif /* TYPES_HPP */
