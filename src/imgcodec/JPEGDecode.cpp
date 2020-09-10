#include "include/imgcodec/JPEGDecoder.hpp"
#include "include/imgcodec/markers.hpp"

#ifdef __linux__ 
#include <arpa/inet.h>
#endif

#ifdef __WIN32__
#include <winsock.h>
#endif

#include <exception>

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
    return nullptr;
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
    if(!imgfile_.is_open() || !imgfile_.good())
        return;

    uint16_t len;
    imgfile_.read(reinterpret_cast<char*>(&len), 2);
    len = htons(len);

    uint8_t byte;
    std::string comment;
    int size = (int)len - 2;
    int endPos = (int)imgfile_.tellg() + (int)len - 2;
    while(imgfile_.tellg() < endPos)
    {
        imgfile_ >> std::noskipws >> byte;
        if(byte == JPEG_BYTE_FF)
        {
            throw std::runtime_error("jpeg decoder find forbidden simbol in com segment in image");
        }
        comment.push_back(static_cast<char>(byte));
    }
}
// need zigzag 
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

    qtable_.push_back({});
    for(int i = 0; i < 64; ++i)
    {
        imgfile_ >> std::noskipws >> tableid;
        qtable_[qtable].push_back((uint16_t)tableid);
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
    if(imgfile_.is_open() || imgfile_.good())
        return;

    uint16_t lenSeg;
    imgfile_.read(reinterpret_cast<char*>(&lenSeg), 2);
    lenSeg = htons(lenSeg);
    
    int segmentEnd = (int)imgfile_.tellg() + (int)lenSeg - 2;
    while(imgfile_.tellg() > segmentEnd)
    {
        uint8_t tableInfo;
        imgfile_ >> std::noskipws >> tableInfo;
        
        int tableType = (int)((tableInfo & 0x10) >> 4);
        int tableid = (int)(tableInfo & 0x0F);

        uint8_t countSymbols;
        int allSymbolCount;

        for(int i = 0; i < 16; ++i)
        {
            imgfile_ >> std::noskipws >> countSymbols;
            huffmanTable_[tableType][tableid][i].first = (int)countSymbols;
            allSymbolCount += (int)countSymbols;
        }
        
        int i = 0;
        for(int syms = 0; syms < allSymbolCount; ++syms)
        {
            uint8_t code;
            imgfile_ >> std::noskipws >> code;

            if(huffmanTable_[tableType][tableid][i].first == 0)
            {
                while(huffmanTable_[tableType][tableid][++i].first == 0);
            }

            huffmanTable_[tableType][tableid][i].second.push_back(code);

            if(huffmanTable_[tableType][tableid][i].first == huffmanTable_[tableType][tableid][i].second.size())
                ++i;
        }
        huffmanTree_[tableType][tableid] = HuffmanTree(huffmanTable_[tableType][tableid]);
    }
}

void JPEGDecoder::parseSOS()
{

}

void JPEGDecoder::decodeData()
{

}

}
