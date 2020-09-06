#ifndef JPEGDECODER_HPP
#define JPEGDECODER_HPP

#include <ifstream>

#include "IDecoder.hpp"

namespace imp
{

class JPEGDecoder : public IDecoder
{
public:
    enum ResultCode
    {
        SUCCESS,
        TERMINATE,
        ERROR,
        DECODE_INCOMPLETE,
        DECODE_DONE
    };

    JPEGDecoder();
    ~JPEGDecoder();

    bool open(std::string& filename) override;
    unsigned char* getRawData() override;

private:
    ResultCode parseSegmentInfo(uint16_t byte);

    void parseAPP0();
    void parseCOM();

    /// Quantialize table
    void parseDQT();

    /// Baseline DCT
    void parseSOF0();

    /// Huffman table
    void parseDHT();

    /// Start of Scan
    void parseSOS();

    std::string filename_;
    std::ifstream imgfile_;


};

}
#endif /* JPEGDECODER_HPP */
