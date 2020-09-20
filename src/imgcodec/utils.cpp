#include "include/imgcodec/utils.hpp"

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

    const std::pair<const int, const int> zzOrderToMatIndices( const int zzindex )
    {
        static const std::pair<const int, const int> zzorder[64] =
        {
            {0,0},
            {0,1}, {1,0},         
            {2,0}, {1,1}, {0,2},
            {0,3}, {1,2}, {2,1}, {3,0},
            {4,0}, {3,1}, {2,2}, {1,3}, {0,4},
            {0,5}, {1,4}, {2,3}, {3,2}, {4,1}, {5,0},
            {6,0}, {5,1}, {4,2}, {3,3}, {2,4}, {1,5}, {0,6},
            {0,7}, {1,6}, {2,5}, {3,4}, {4,3}, {5,2}, {6,1}, {7,0},
            {7,1}, {6,2}, {5,3}, {4,4}, {3,5}, {2,6}, {1,7},
            {2,7}, {3,6}, {4,5}, {5,4}, {6,3}, {7,2},
            {7,3}, {6,4}, {5,5}, {4,6}, {3,7},
            {4,7}, {5,6}, {6,5}, {7,4},
            {7,5}, {6,6}, {5,7},
            {6,7}, {7,6},
            {7,7}
        };
        
        return zzorder[zzindex];
    }
}

}
