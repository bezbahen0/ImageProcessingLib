#ifndef MAT_HPP
#define MAT_HPP

#include "types.hpp"
namespace ip
{
struct Size
{
    int width;
    int height;
    Size() : width(0), height(0)
    {
    }
    Size(int width, int height) : width(width), height(height)
    {
    }
}

class Mat
{

public:
    Mat();
    Mat(int width, int height, int depth, int channels);
    Mat(Size size, int depth, int channels);
    ~Mat();

    int rows() const;
    int cols() const;
    Size size() const;
    int channels() const;

private:
    int cols_;
    int rows_;

    int width_;
    int height_;

    Size size_;
    
    int channels_;
};

}
#endif /* MAT_HPP */
