#ifdef __linux__ 
#include <arpa/inet.h>
#endif

#ifdef __WIN32__
#include <winsock.h>
#endif

#include <bitset>

#include "include/imgcodec/JPEGDecoder.hpp"
#include "include/imgcodec/markers.hpp"
#include "include/imgcodec/utils.hpp"

namespace imp
{

JPEGDecoder::JPEGDecoder()
{
}

JPEGDecoder::~JPEGDecoder()
{
    for(auto i = qtable_.begin(); i != qtable_.end(); ++i)
    {
        i -> shrink_to_fit();
    }
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            for(int k = 0; k != huffmanTable_[i][j].size(); ++k)
            {
                huffmanTable_[i][j][k].second.shrink_to_fit();
            }
            huffmanTree_[i][j].clear();
        }
    }
    qtable_.shrink_to_fit();
    imgfile_.close();
}

bool JPEGDecoder::open(std::string filename) 
{
    imgfile_.open(filename, std::ios::in | std::ios::binary);

    if(!imgfile_.is_open() && !imgfile_.good())
        return false;

    filename_ = filename;
    
    ResultCode status = decodeImageFile();

    if(status == ResultCode::DECODE_DONE)
    {
        if(decodeData() != ResultCode::SUCCESS)
            return false;
    }
    else
    {
        imgfile_.close();
        return false;
    }
    imgfile_.close();

    return true;
}

unsigned char* JPEGDecoder::getRawData()
{
    return createImageWithMCU(mcu_).data();
}

Mat JPEGDecoder::getMatrix()
{
    return createImageWithMCU(mcu_);
}

Mat JPEGDecoder::createImageWithMCU(std::vector<MCU>& MCU)
{
    int width = imageMetadata_.width % 8 == 0 ? imageMetadata_.width : imageMetadata_.width + 8 - (imageMetadata_.width % 8); 
    int height = imageMetadata_.height % 8 == 0 ? imageMetadata_.height : imageMetadata_.height + 8 - (imageMetadata_.height % 8); 
   
    int count = 0;
    Mat mat = Mat::zeros(height, width, 1, imageMetadata_.channels);
    for(int y = 0; y <= width; y += 8)
    {
        for(int x = 0; x <= height; x += 8)
        {
            auto block = MCU[count].getAllMatrix();
            for(int v = 0; v < 8; ++v)
            {
                for(int u = 0; u < 8; ++u)
                {
                    for(int i = 0; i < imageMetadata_.channels; ++i)
                    {
                        mat.at<int>(y + v, x + u, i) = block[i][v][u];
                    }
                }
            }
            count++;
        }
    }
    return mat;
}

JPEGDecoder::ResultCode JPEGDecoder::decodeImageFile()
{
    if (!imgfile_.is_open() || !imgfile_.good())
        return ResultCode::ERROR;
    
    Uint8 byte;
    
    while(imgfile_ >> std::noskipws >> byte)
    {
        if (byte == JPEG_BYTE_FF)
        {
            imgfile_ >> std::noskipws >> byte;
            
            ResultCode code = parseSegmentInfo(byte);
            
            if(code == ResultCode::TERMINATE)
            {
                return ResultCode::TERMINATE;
            }
            else if(code == ResultCode::DECODE_INCOMPLETE)
            {
                return ResultCode::DECODE_INCOMPLETE;
            }
        }
        else
        {
            return ResultCode::ERROR;
        }
    }
    
    return ResultCode::DECODE_DONE;
}

JPEGDecoder::ResultCode JPEGDecoder::parseSegmentInfo(Uint8 byte)
{
    if(JPEG_BYTE_FF == byte || byte == JPEG_BYTE_0)
    {
        return ResultCode::ERROR;
    }
    else if(byte == JPEG_APP0)
    {
        return parseAPP0();
    }
    else if(byte == JPEG_COM)
    {
        return parseCOM();
    }
    else if(byte == JPEG_SOF0)
    {
        return parseSOF0();
    }
    else if(byte == JPEG_DQT)
    {
        return parseDQT();
    }
    else if(byte == JPEG_DHT)
    {
        return parseDHT();
    }
    else if(byte == JPEG_SOS)
    {
        return parseSOS();
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

JPEGDecoder::ResultCode JPEGDecoder::parseAPP0()
{
    if (!imgfile_.is_open() || !imgfile_.good())
        return ResultCode::ERROR;
    
    Uint16 lenByte = 0;
    Uint8 byte = 0;
    
    imgfile_.read(reinterpret_cast<char *>(&lenByte), 2);
    lenByte = htons(lenByte);
    std::size_t curPos = imgfile_.tellg();
    
    imgfile_.seekg(5, std::ios_base::cur);
    
    Uint8 majVersionByte, minVersionByte;
    imgfile_ >> std::noskipws >> majVersionByte >> minVersionByte;
    
    std::string majorVersion = std::to_string(majVersionByte);
    std::string minorVersion = std::to_string((int)(minVersionByte >> 4));
    minorVersion +=  std::to_string((int)(minVersionByte & 0x0F));
    
    Uint8 densityByte;
    imgfile_ >> std::noskipws >> densityByte;
    
    std::string densityUnit = "";
    switch(densityByte)
    {
        case 0x00: densityUnit = "Pixel Aspect Ratio"; break;
        case 0x01: densityUnit = "Pixels per inch (DPI)"; break;
        case 0x02: densityUnit = "Pixels per centimeter"; break;
    }
    
    Uint16 xDensity = 0, yDensity = 0;
    
    imgfile_.read(reinterpret_cast<char *>(&xDensity), 2);
    imgfile_.read(reinterpret_cast<char *>(&yDensity), 2);
    
    xDensity = htons(xDensity);
    yDensity = htons(yDensity);
    
    Uint8 xThumb = 0, yThumb = 0;
    imgfile_ >> std::noskipws >> xThumb >> yThumb;        
    imgfile_.seekg(3 * xThumb * yThumb, std::ios_base::cur);

    return ResultCode::SUCCESS; 
}

JPEGDecoder::ResultCode JPEGDecoder::parseCOM()
{
    if(!imgfile_.is_open() || !imgfile_.good())
        return ResultCode::ERROR;

    Uint16 len;
    imgfile_.read(reinterpret_cast<char*>(&len), 2);
    len = htons(len);

    Uint8 byte;
    std::string comment;
    int size = (int)len - 2;
    int endPos = (int)imgfile_.tellg() + (int)len - 2;
    while(imgfile_.tellg() < endPos)
    {
        imgfile_ >> std::noskipws >> byte;
        if(byte == JPEG_BYTE_FF)
        {
            return ResultCode::ERROR;
        }
        comment.push_back(static_cast<char>(byte));
    }

    return ResultCode::SUCCESS;
}
// need zigzag 
JPEGDecoder::ResultCode JPEGDecoder::parseDQT()
{
    if(!imgfile_.is_open() || !imgfile_.good())
        return ResultCode::ERROR;

    Uint16 lenByte = 0;
    Uint8 lenValTable;
    Uint8 tableid;

    imgfile_.read(reinterpret_cast<char*>(&lenByte), 2);
    lenByte = htons(lenByte);

    lenByte -= 2;

    imgfile_ >> std::noskipws >> lenValTable;

    int precision = lenValTable >> 4;
    int qtable = lenValTable & 0x0F;

    qtable_.push_back({});
    for(int i = 0; i < 64; ++i)
    {
        imgfile_ >> std::noskipws >> tableid;
        qtable_[qtable].push_back((Uint16)tableid);
    }
    
    return ResultCode::SUCCESS;
}

JPEGDecoder::ResultCode JPEGDecoder::parseSOF0()
{
    if(!imgfile_.is_open() || !imgfile_.good())
        return ResultCode::ERROR; 

    Uint16 length, height, width;
    Uint8 precision, channels;

    imgfile_.read(reinterpret_cast<char*>(&length), 2);
    length = htons(length);

    imgfile_ >> std::noskipws >> precision;

    imgfile_.read(reinterpret_cast<char*>(&height), 2);
    imgfile_.read(reinterpret_cast<char*>(&width), 2);
    height = htons(height);
    width = htons(width);

    imgfile_ >> std::noskipws >> channels;

    imageMetadata_.height = (int)height;
    imageMetadata_.width = (int)width;
    imageMetadata_.channels = (int)channels;

    bool sampled = true;
    Uint8 id, samplingFactor, idQtable;
    for(int i = 0; i < (int)channels; ++i)
    {
        imgfile_ >> std::noskipws >> id >> samplingFactor >> idQtable; 

        if((samplingFactor >> 4 ) != 1 || (samplingFactor & 0x0F) != 1)
            sampled = false;
    }

    return ResultCode::SUCCESS;
}

JPEGDecoder::ResultCode JPEGDecoder::parseDHT()
{
    if(!imgfile_.is_open() || !imgfile_.good())
        return ResultCode::ERROR;

    Uint16 lenSeg;
    imgfile_.read(reinterpret_cast<char*>(&lenSeg), 2);
    lenSeg = htons(lenSeg);
    
    int segmentEnd = (int)imgfile_.tellg() + (int)lenSeg - 2;
    while(imgfile_.tellg() < segmentEnd)
    {
        Uint8 tableInfo;
        imgfile_ >> std::noskipws >> tableInfo;
        
        int tableType = int((tableInfo & 0x10) >> 4);
        int tableid = int(tableInfo & 0x0F);

        Uint8 countSymbols;
        int allSymbolCount = 0;

        for(int i = 0; i < 16; ++i)
        {
            imgfile_ >> std::noskipws >> countSymbols;
            huffmanTable_[tableType][tableid][i].first = (int)countSymbols;
            allSymbolCount += (int)countSymbols;
        }
        
        int i = 0;
        for(int syms = 0; syms < allSymbolCount; ++syms)
        {
            Uint8 code;
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

    return ResultCode::SUCCESS;
}

JPEGDecoder::ResultCode JPEGDecoder::parseSOS()
{
    if(!imgfile_.is_open() || !imgfile_.good())
        return ResultCode::ERROR;

    Uint16 lenSeg;
    imgfile_.read(reinterpret_cast<char*>(&lenSeg), 2);
    lenSeg = htons(lenSeg);

    Uint8 byte;
    imgfile_ >> std::noskipws >> byte;
    int channels = (int)byte;

    if(channels < 1 || channels > 4)
        return ResultCode::DECODE_INCOMPLETE;

    imageMetadata_.channels = channels;

    for(int i = 0; i <  channels; ++i)
    {
        Uint16 compInfo;
        imgfile_.read(reinterpret_cast<char*>(&compInfo), 2);
    }

    /// skip [00], [3F], [00]
    for(int i = 0; i < 3; ++i)
    {
        imgfile_ >> std::noskipws >> byte;
    }
   
    return parseImgData();
}

JPEGDecoder::ResultCode JPEGDecoder::parseImgData()
{
    if(!imgfile_.is_open() || !imgfile_.good())
        return ResultCode::ERROR;
    
    Uint8 byte;
    while(imgfile_ >> std::noskipws >> byte)
    {
        if(byte == JPEG_BYTE_FF)
        {
            Uint8 prevByte = byte;
            imgfile_ >> std::noskipws >> byte;

            if(byte == JPEG_EOI)
            {
                return ResultCode::SUCCESS;
            }
            std::bitset<8> bits1(prevByte);
            imageData_.append(bits1.to_string());
        }
        std::bitset<8> bits(byte);
        imageData_.append(bits.to_string());
    }

    return ResultCode::DECODE_INCOMPLETE;
}

JPEGDecoder::ResultCode JPEGDecoder::byteScanData()
{
    if(imageData_.empty())
        return ResultCode::DECODE_INCOMPLETE;

    for(int i = 0; i < imageData_.size() - 8; i += 8)
    {
        std::string temp = imageData_.substr(i, 8);
        
        if(temp == "11111111")
        {
            if(i + 8 < imageData_.size() - 8)
            {
                std::string nextTemp = imageData_.substr(i + 8, 8);
                if(nextTemp == "00000000")
                    imageData_.erase(i + 8, 8);
            }
        }
    }

    return ResultCode::SUCCESS;
}

JPEGDecoder::ResultCode JPEGDecoder::decodeData()
{
    ResultCode status = byteScanData();
    if(status != ResultCode::SUCCESS)
        return status;

    const int HT_DC = 0;
    const int HT_AC = 1;

    int it = 0;
    int chan = imageMetadata_.channels;
    std::size_t MCUcount = (imageMetadata_.height * imageMetadata_.width) / 64;
    for(std::size_t i = 0; i < MCUcount; ++i)
    {
        std::vector<std::vector<int>> RLE(chan);

        for(int channelId = 0; channelId < RLE.size(); ++channelId)
        {
            std::string bits = "";

            int huffmanTableId = channelId == 0 ? 0 : 1;
            while(true)
            {
                bits += imageData_[it];
                std::string value = huffmanTree_[HT_DC][huffmanTableId].contains(bits);

                if(!utils::isStringWhiteSpace(value))
                {
                    if(value != "EOB")
                    {
                        int count = Uint8(std::stoi(value)) >> 4;
                        int category = Uint8(std::stoi(value)) &  0x0F;
                        int DC = utils::bitStringtoValue(imageData_.substr(it + 1, category)); 

                        it += category + 1;
                        bits = "";

                        RLE[channelId].push_back(count);
                        RLE[channelId].push_back(DC);
                        break;
                    }
                    else
                    {
                        RLE[channelId].push_back(0);
                        RLE[channelId].push_back(0);

                        bits = "";
                        it++;
                        break;
                    }
                }
                else
                {
                    it++;
                }
            }

            bits = "";
            int ACcodesCount = 0;
            while(true)
            {
                if(ACcodesCount == 63)
                    break;

                bits += imageData_[it];
                std::string value = huffmanTree_[HT_AC][huffmanTableId].contains(bits);

                if(!utils::isStringWhiteSpace(value))
                {
                    if(value != "EOB")
                    {
                        int count = Uint8(std::stoi(value)) >> 4;
                        int category = Uint8(std::stoi(value)) &  0x0F;
                        int AC = utils::bitStringtoValue(imageData_.substr(it + 1, category)); 

                        it += category + 1;
                        bits = "";

                        RLE[channelId].push_back(count);
                        RLE[channelId].push_back(AC);

                        ACcodesCount += count + 1;
                    }
                    else
                    {
                        RLE[channelId].push_back(0);
                        RLE[channelId].push_back(0);

                        bits = "";
                        it++;
                        break;
                    }
                }
                else
                {
                    it++;
                }
            }

            if(RLE[channelId].size() == 2)
            {
                bool allZeros = true;
                for(auto i = RLE[channelId].begin(); i != RLE[channelId].end(); ++i)
                {
                    if(*i != 0)
                    {
                        allZeros = false;
                        break;
                    }
                }
                if(allZeros)
                {
                    RLE[channelId].pop_back();
                    RLE[channelId].pop_back();
                }
            }
        }
        mcu_.push_back(MCU(RLE, qtable_));
    }

    return ResultCode::SUCCESS;
}

}
