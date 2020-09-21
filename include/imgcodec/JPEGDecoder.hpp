#ifndef JPEGDECODER_HPP
#define JPEGDECODER_HPP

#include <fstream>

#include "IDecoder.hpp"
#include "HuffmanTree.hpp"
#include "MCU.hpp"
#include "include/types.hpp"

namespace imp
{

class JPEGDecoder : public IDecoder
{
public:
    enum ResultCode {
        SUCCESS,              // OK!
        TERMINATE,            // algorithm not support
        ERROR,                // error, not asasiate with process decode
        DECODE_INCOMPLETE,    // decode bad complete (jpeg image not valid)
        DECODE_DONE           // decode complete 
    };

    JPEGDecoder();
    virtual ~JPEGDecoder();

    virtual bool open(std::string filename) override;
    virtual unsigned char* getRawData() override;
    virtual Mat getMatrix() override;

    static std::shared_ptr<JPEGDecoder> create()
    {
        return std::make_shared<JPEGDecoder>();
    }

protected:
    Mat createImageWithMCU(std::vector<MCU>& MCU);

    ResultCode decodeImageFile();
    ResultCode parseSegmentInfo(Uint8 byte);

    ResultCode parseAPP0();

    /// comment segment parse
    ResultCode parseCOM();

    /// Quantialize table
    ResultCode parseDQT();

    /// Baseline DCT
    ResultCode parseSOF0();

    /// Huffman table parse
    ResultCode parseDHT();

    /// Start of Scan
    /// contains channels on image
    ResultCode parseSOS(); 

    ResultCode parseImgData();

    ResultCode byteScanData();
    /// decode encodeing data 
    ResultCode decodeData();

    ImgMeta imageMetadata_;
    std::string imageData_;

    std::string filename_;
    std::ifstream imgfile_;

    std::vector<std::vector<Uint16>> qtable_;

    // 4 huffman tables
    // [type][idtable][id array*id symbol count*]
    // in pair int - count symbols
    //         std::vector<uint8_t> - values codes
    HuffmanTableType huffmanTable_[2][2]; 
    HuffmanTree huffmanTree_[2][2];
    std::vector<MCU> mcu_;
};

}
#endif /* JPEGDECODER_HPP */
