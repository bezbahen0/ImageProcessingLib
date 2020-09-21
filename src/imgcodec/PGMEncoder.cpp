#include "include/imgcodec/PGMEncoder.hpp"
#include "include/types.hpp"

#include <fstream>
#include <exception>

namespace imp
{
    bool PGMEncoder::writeImage(std::string filename, Mat& image)
    {
        if(image.channels() != GRAY)
            throw std::runtime_error("image is not a grayscale use ppm if you need save rgb, or use others format");

        std::ofstream file(filename, std::ios::out);
        if(!file.is_open() || !file.good())
            return false;

        file << "P5 " << std::endl;
        file << "#hi" << std::endl;
        file << image.size().width << " " << image.size().height << std::endl;
        for(int i = 0; i != image.rows(); ++i)
        {
            for(int j = 0; j != image.cols(); ++j)
            {
                file << image.at<Uint8>(i, j) << image.at<Uint8>(i, j) << image.at<Uint8>(i, j);
            }
        }
    
        file.close();
        return true;
    }
}
