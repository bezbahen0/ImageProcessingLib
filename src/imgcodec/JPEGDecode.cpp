#include "include/imgcodec/JPEGDecoder.hpp"
#include "include/imgcodec/markers.hpp"

#ifdef __linux__ 
#include <arpa/inet.h>
#endif

#ifdef __WIN32__
#include <winsock.h>
#endif

namespace imp
{

JPEGDecoder::JPEGDecoder()
{
}

JPEGDecoder::~JPEGDecoder()
{
    imgfile_.close();
}

bool JPEGDecoder::open(std::string filename) 
{
    imgfile_.open(filename, std::ios::in | std::ios::binary);

    if(!imgfile_.is_open() && !imgfile_.good())
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
                imgfile_.close();
                return false;
            }
        }
        else
        {   
            imgfile_.close();
            return false;
        }
    }

    decodeData();
    
    imgfile_.close();
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
    else if(byte == JPEG_APP0)
    {
        parseAPP0();
        return ResultCode::SUCCESS;
    }
    else if(byte == JPEG_COM)
    {
        parseCOM();
        return ResultCode::SUCCESS;
    }
    else if(byte == JPEG_SOF0)
    {
        return parseSOF0();
    }
    else if(byte == JPEG_DQT)
    {
        parseDQT();
        return ResultCode::SUCCESS;
    }
    else if(byte == JPEG_DHT)
    {
        parseDHT();
        return ResultCode::SUCCESS;
    }
    else if(byte == JPEG_SOS)
    {
        parseSOS();
        return ResultCode::SUCCESS;
    }
    else if(byte == JPEG_SOI)
    {
        return ResultCode::SUCCESS;
    }
    else if(byte == JPEG_SOF1)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF1)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF1)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF2)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF3)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF5)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF6)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF7)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF9)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF10)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF11)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF13)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF14)
    {
        return ResultCode::TERMINATE;
    }
    else if(byte == JPEG_SOF15)
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
    uint8_t tableid;

    imgfile_.read(reinterpret_cast<char*>(&lenByte), 2);
    lenByte = htons(lenByte);

    lenByte -= 2;

    int precision = lenValTable >> 4;
    int qtable = lenValTable & 0x0F;

    Qtable_.push_back({});
    for(int i = 0; i < 64; ++i)
    {
        imgfile_ >> std::noskipws >> tableid;
        Qtable_[qtable].push_back((uint16_t)tableid);
    }
}

JPEGDecoder::ResultCode JPEGDecoder::parseSOF0()
{
    //not full 
    uint16_t length, height, width;
    uint8_t precision, channels;

    imgfile_.read(reinterpret_cast<char*>(&length), 2);
    imgfile_.read(reinterpret_cast<char*>(&precision), 1);
    
    length = htons(length);

    imgfile_.read(reinterpret_cast<char*>(&height), 2);
    imgfile_.read(reinterpret_cast<char*>(&width), 2);
    imgfile_.read(reinterpret_cast<char*>(&channels), 1);

    height = htons(height);
    width = htons(width);

    imageMetadata_.height = (int)height;
    imageMetadata_.width = (int)width;
    imageMetadata_.channels = (int)channels;

    uint8_t id, samplingFactor, idQtable;
    for(int i = 0; i < (int)channels; ++i)
    {
        imgfile_ >> std::noskipws >> id >> samplingFactor >> idQtable; 

        if((samplingFactor >> 4 ) != 1 || (samplingFactor & 0x0F) != 1)
            return ResultCode::TERMINATE;
    }

    return ResultCode::SUCCESS;
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
