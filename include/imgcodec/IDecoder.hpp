#ifndef IDECODER_HPP
#define IDECODER_HPP

#include <string>

class IDecoder
{
public:
    virtual void open(std::string& filename){}
    virtual unsigned char* getRawData(){}
};

#endif /* IDECODER_HPP */
