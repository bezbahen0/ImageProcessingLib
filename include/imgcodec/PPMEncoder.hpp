#ifndef PPMENCODER_HPP
#define PPMENCODER_HPP

#include "IEncoder.hpp"

namespace imp
{

class PPMEncoder : public IEncoder
{
public:
    virtual bool writeImage(std::string filename, Mat& image) override;
};

}
#endif /*PPMENCODER_HPP */
