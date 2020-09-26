#ifndef MAT_HPP
#define MAT_HPP

#include "types.hpp"

#include <tuple>
#include <stdexcept>

namespace imp
{
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

    template<typename T>
    T& at(int rows, int cols)
    {
        if((std::tie(rows_, cols_)) < std::tie(rows, cols))
            throw std::out_of_range("(rows or cols) > (rows_ or cols_)");

        return (T&)data_[rows_ * rows + cols];
    }

    template<typename T>
    T& at(int rows, int cols, int channels)
    {
        if(std::tie(rows_, cols_, channels_) < std::tie(rows, cols, channels))
            throw std::out_of_range("(rows or cols or channels) > (rows_ or cols_ or channels_)"); 

        return (T&)data_[(channels * rows_ * cols_) + (cols * rows_) + rows];
    }

    static Mat zeros(int rows, int cols, int depth, int channels);

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
