#ifndef LOADSAVE_HPP
#define LOADSAVE_HPP

#include "imgcodec.hpp"
#include "Mat.hpp"

namespace imp
{
    using DecoderPtr = std::shared_ptr<IDecoder>;
    using EncoderPtr = std::shared_ptr<IEncoder>;

    std::string getExtension(std::string filename);

    Mat imread(std::string filename);
    void imwrite(std::string filename, Mat& image);
    
    DecoderPtr getDecoder(std::string extension);
    EncoderPtr getEncoder(std::string extension);
}

#endif /* LOADSAVE_HPP */
