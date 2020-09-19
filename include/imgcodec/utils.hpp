#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <cctype>
#include <cmath>

namespace imp
{

namespace utils
{
    const Int16 bitStringtoValue(const std::string& bitStr)
    {
        if (bitStr == "")
            return 0x0000;
        
        Int16 value = 0x0000;
        
        char sign = bitStr[0];
        int factor = sign == '0' ? -1 : 1;
            
        for (auto i = 0; i < bitStr.size(); ++i)
        {
            if (bitStr[i] == sign)
                value += Int16(std::pow(2, bitStr.size() - 1 - i));
        }
        
        return factor * value;
    }
 
    bool isWhiteSpace(const char ch)
    {
        return iscntrl(ch) || isblank(ch) || isspace(ch);
    }

    bool isStringWhiteSpace(const std::string& str)
    {
        for(auto i = str.begin(); i != str.end(); ++i)
        {
            if(!isWhiteSpace(*i))
            {
                return false;
            }
        }
        return true;
    }
}

}

#endif /* UTILS_HPP */
