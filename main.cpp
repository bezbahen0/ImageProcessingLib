#include "include/imgcodec/JPEGDecoder.hpp"
#include "include/loadsave.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    imp::Mat mat = imp::imread(argv[1]);
    std::cout << mat.at<float>(133, 133, 0) << std::endl;
    imp::imwrite(argv[2], mat);
    return 0;
}
