#include "include/imgcodec/PPMEncoder.hpp"
#include "include/types.hpp"

#include <fstream>
#include <exception>

namespace imp
{
    bool PPMEncoder::writeImage(std::string filename, Mat& image)
    {
        if(image.channels() != RGB)
            throw std::runtime_error("image is not a rgb use pgm if you need save grayscale, or use others format");

        std::ofstream file(filename, std::ios::out);
        if(!file.is_open() || !file.good())
            return false;

        file << "P6 " << std::endl;
        file << "#hi" << std::endl;
        file << image.size().width << " " << image.size().height << std::endl;
        for(int i = 0; i != image.rows(); ++i)
        {
            for(int j = 0; j != image.cols(); ++j)
            {
                file << image.at<Uint8>(i, j, 0) << image.at<Uint8>(i, j, 1) << image.at<Uint8>(i, j, 2);
            }
        }
    
        file.close();
        return true;

    }

}
