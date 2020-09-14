#include "include/loadsave.hpp"

namespace imp
{
    std::string getExtension(std::string filename)
    {
        auto const pos = filename.find_last_of('.');
        return filename.substr(pos + 1);
    }

    Mat imread(std::string filename)
    {
        std::string extension = getExtension(filename);
        DecoderPtr decoder = getDecoder(extension);

        decoder -> open(filename);
        return decoder -> getMatrix();
    }

    void imwrite(std::string filename, Mat& image)
    {
        std::string extension = getExtension(filename);
        EncoderPtr encoder = getEncoder(extension);
        encoder -> writeImage(filename, image);
    }

    DecoderPtr getDecoder(std::string extension)
    {
        DecoderPtr decoder = nullptr;
        if(extension == "jpeg" || extension == "jpg" || extension == "jpe" ||
                extension == "jif" || extension == "jfif" || extension == "jfi")
        {
            decoder = std::make_shared<JPEGDecoder>(); 
        }

        if(decoder == nullptr)
        {
            throw std::runtime_error("image type isn't supporte or invalid");
        }
        return decoder;
    }

    EncoderPtr getEncoder(std::string extension)
    {
        EncoderPtr encoder = nullptr;
        if(extension == "ppm")
        {
            encoder = PPMEncoder::create();
        }
        else if(extension == "pgm")
        {
            encoder = PGMEncoder::create();
        }

        if(encoder == nullptr)
        {
            throw std::runtime_error("image type isn't supporte or invalid");
        }
        
        return encoder;
    }
}
