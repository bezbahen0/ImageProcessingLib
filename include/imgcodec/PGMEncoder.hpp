#ifndef PGMECODER_HPP
#define PGMECODER_HPP

#include "include/imgcodec/IEncoder.hpp"

namespace imp
{

class PGMEncoder : public IEncoder
{
public:
    virtual bool writeImage(std::string filename, Mat& image) override;

};

}
#endif /* PGMECODER_HPP */
