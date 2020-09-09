#include "include/Mat.hpp"

namespace imp
{

Mat::Mat()
{
}

Mat::Mat(int rows, int cols, int depth, int channels):
    depth_(depth), channels_(channels), size_(Size(cols, rows)), rows_(rows), cols_(cols)
{
    data_ = new unsigned char[size_.width * size_.height * channels_];
}

Mat::Mat(Size size, int depth, int channels):
    size_(size), depth_(depth), channels_(channels), rows_(size_.height), cols_(size_.width)  
{
    data_ = new unsigned char[size_.width * size_.height * channels_];
}

Mat::~Mat()
{
    delete[] data_;
}

int Mat::rows() const
{
    return rows_;
}

int Mat::cols() const
{
    return cols_;
}

Size Mat::size() const
{
    return size_;
}

int Mat::depth() const
{
    return depth_;
}

int Mat::channels() const
{
    return channels_;
}

unsigned char* Mat::data() const
{
    return data_;
}

}
