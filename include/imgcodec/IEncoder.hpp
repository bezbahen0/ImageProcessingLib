#ifndef IENCODER_HPP
#define IENCODER_HPP 

#include <string>

#include "include/Mat.hpp"

namespace imp
{

class IEncoder
{
public:
    virtual bool writeImage(std::string filename, Mat& image){ return false; }
};

}
#endif /* IENCODER_HPP */
