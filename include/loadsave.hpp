#ifndef LOADSAVE_HPP
#define LOADSAVE_HPP

#include "Mat.hpp"

namespace imp
{
    Mat imread(std::string filename);
    void imwrite(std::string filename, Mat image);
}

#endif /* LOADSAVE_HPP */
