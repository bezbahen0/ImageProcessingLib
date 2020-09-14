#ifndef IDECODER_HPP
#define IDECODER_HPP

#include <string>

#include "include/types.hpp"
#include "include/Mat.hpp"

namespace imp
{

class IDecoder
{
public:
    virtual bool open(std::string filename){ return false; }
    virtual unsigned char* getRawData(){ return nullptr; }
    virtual Mat getMatrix(){ return Mat(); }
};

}
#endif /* IDECODER_HPP */
