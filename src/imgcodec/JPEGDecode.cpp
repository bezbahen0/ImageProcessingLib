#include "include/imgcodec/JPEGDecoder.cpp"

namespace imp
{

JPEGDecoder::JPEGDecoder()
{
}

JPEGDecoder::~JPEGDecoder()
{
    imgfile_.close();
}

bool JPEGDecoder::open(std::string& filename)
{
    imgfile_.open(filename, std::io:in | std::io::binary);

    if(!imgfile_.isopen() && !imgfile_.good())
    {
        return false;
    }
    filename_ = filename;

    uint8_t byte;
    while(imgfile_ >> std::noskipws >> byte)
    {
        if(byte == JPEG_BYTE_FF)
        {
            imgfile_ >> std::noskipws >> byte;
            
            ResultCode code = parseSegmentInfo(byte);

            if(code != ResultCode::SUCCESS)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    decodeData();

    return true;
}

unsigned char* JPEGDecoder::getRawData()
{
}

JPEGDecoder::ResultCode JPEGDecoder::parseSegmentInfo(uint16_t byte)
{
    if(JPEG_BYTE_FF == byte || byte == JPEG_BYTE_0)
    {
        return ResultCode::ERROR;
    }
    if else(byte == JPEG_APP0)
    {
        parseAPP0();
        return ResultCode::SUCCESS;
    }
    if else(byte == JPEG_COM)
    {
        parseCOM();
        return ResultCode::SUCCESS;
    }
    if else(byte == JPEG_SOF0)
    {
        parseSOF0();
        return ResultCode::SUCCESS;
    }
    if els(byte == JPEG_DQT)
    {
        parseDQT();
        return ResultCode::SUCCESS;
    }
    if else(byte == JPEG_DHT)
    {
        parseDHT();
        return ResultCode::SUCCESS;
    }
    if else(byte == JPEG_SOS)
    {
        parseSOS();
        return ResultCode::SUCCESS;
    }
    if else(byte == JPEG_SOI)
    {
        return ResultCode::SUCCESS;
    }
    if else(byte == JPEG_SOF1)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF1)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF1)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF2)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF3)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF5)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF6)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF7)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF9)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF10)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF11)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF13)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF14)
    {
        return ResultCode::TERMINATE;
    }
    if else(byte == JPEG_SOF15)
    {
        return ResultCode::TERMINATE;
    }

    return ResultCode::SUCCESS;
}

void JPEGDecoder::parseAPP0()
{

}

void JPEGDecoder::parseCOM()
{

}

void JPEGDecoder::parseDQT()
{
    if(!imgfile_.is_open() || !imgfile_.good())
        return;

    uint16_t lenByte = 0;
    uint8_t lenValTable;
    uint8_t tableId;

    imgfile_.read(reinterpret_cast<char*>(&lenByte), 2);
    lenByte = htons(lenByte);

    lenByte -= 2;

    int precision = lenValTable >> 4;
    int qtable = lenValTable & 0x0F;

    //Qtable_.push_back({});
    for(int i = 0; i < 64; ++i)
    {
        imgfile_ >> std::noskipws >> tableid;
        Qtable_[qtable].push_back((uint16_t)tableid);
    }
}

void JPEGDecoder::parseSOF0()
{

}

void JPEGDecoder::parseDHT()
{

}

void JPEGDecoder::parseSOS()
{

}

void JPEGDecoder::decodeData()
{

}

}
