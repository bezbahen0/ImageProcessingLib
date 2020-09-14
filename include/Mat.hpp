#ifndef MAT_HPP
#define MAT_HPP

#include "types.hpp"

namespace imp
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
};
// need overrload operator= to prevent memory leaks and implements clone function
class Mat
{

public:
    Mat();
    Mat(int rows, int cols, int depth, int channels);
    Mat(Size size, int depth, int channels);
    Mat(int rows, int cols, int depth, int channels, void* data);
    Mat(Size size, int depth, int channels, void* data);
    ~Mat();

    int rows() const;
    int cols() const;
    Size size() const;
    int depth() const;
    int channels() const;
    bool empty() const;

    unsigned char* data() const;
//need thist change
    template<typename T>
    T& at(int rows, int cols)
    {
        return reinterpret_cast<T&>(data_[rows + cols]);
    }
//this too
    template<typename T>
    T& at(int rows, int cols, int channels)
    {
        return reinterpret_cast<T&>(data_[channels + rows + cols]);
    }

private:
    int cols_;
    int rows_;

    Size size_;
    
    int depth_;
    int channels_;
    unsigned char* data_;
};

}
#endif /* MAT_HPP */
