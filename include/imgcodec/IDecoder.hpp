#ifndef IDECODER_HPP
#define IDECODER_HPP

#include <string>

class IDecoder
{
public:
    virtual bool open(std::string filename){ return false; }
    virtual unsigned char* getRawData(){}
};

#endif /* IDECODER_HPP */
