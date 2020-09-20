#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <cctype>
#include <cmath>
#include <utility>

#include "include/types.hpp"

namespace imp
{

namespace utils
{
    const Int16 bitStringtoValue(const std::string& bitStr);
 
    bool isWhiteSpace(const char ch);

    bool isStringWhiteSpace(const std::string& str);

    const std::pair<const int, const int> zzOrderToMatIndices( const int zzindex );
}

}

#endif /* UTILS_HPP */
