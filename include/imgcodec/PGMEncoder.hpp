#ifndef PGMECODER_HPP
#define PGMECODER_HPP

#include "IEncoder.hpp"

namespace imp
{

class PGMEncoder : public IEncoder
{
public:
    virtual bool writeImage(std::string filename, Mat& image) override;
    static std::shared_ptr<PGMEncoder> create()
    {
        return std::make_shared<PGMEncoder>();
    }
};

}
#endif /* PGMECODER_HPP */
