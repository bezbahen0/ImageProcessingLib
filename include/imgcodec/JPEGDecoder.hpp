#ifndef JPEGDECODER_HPP
#define JPEGDECODER_HPP

#include "IDecoder.hpp"

namespace imp
{

class JPEGDecoder : public IDecoder
{
public:
    JPEGDecoder();
    ~JPEGDecoder();

    void open(std::string& filename) override;
    unsigned char* getRawData() override;

private:

};

}
#endif /* JPEGDECODER_HPP */
