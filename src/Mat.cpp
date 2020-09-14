#include "include/Mat.hpp"

namespace imp
{

Mat::Mat()
{
    data_ = new unsigned char[0];
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
//need this change
Mat::Mat(int rows, int cols, int depth, int channels, void* data):
    rows_(rows), cols_(cols), depth_(depth), channels_(channels), size_(Size(cols, rows))
{
    data_ = new unsigned char[cols * rows * channels_];
}
//need this change
Mat::Mat(Size size, int depth, int channels, void* data):
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

bool Mat::empty() const
{
    return data_ == nullptr;
}

unsigned char* Mat::data() const
{
    return data_;
}

}
