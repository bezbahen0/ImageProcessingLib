#ifndef JPEGDECODER_HPP
#define JPEGDECODER_HPP

#include <fstream>
#include <array>

#include "IDecoder.hpp"
#include "include/types.hpp"

namespace imp
{
struct ImgMeta
{
    int height;
    int width;
    int channels;
};

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

    virtual bool open(std::string filename) override;
    virtual unsigned char* getRawData() override;

private:
    ResultCode parseSegmentInfo(uint16_t byte);

    void parseAPP0();

    /// comment segment parse
    void parseCOM();

    /// Quantialize table
    void parseDQT();

    /// Baseline DCT
    ResultCode parseSOF0();

    /// Huffman table
    void parseDHT();

    /// Start of Scan
    /// contains channels on image
    void parseSOS(); 

    /// decode encodeing data 
    void decodeData();

    ImgMeta imageMetadata_;

    std::string filename_;
    std::ifstream imgfile_;

    std::vector<std::vector<uint16_t>> Qtable_;


};

}
#endif /* JPEGDECODER_HPP */
