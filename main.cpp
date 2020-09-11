#include "include/Mat.hpp"
#include "include/imgcodec/JPEGDecoder.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    imp::Mat img(10, 10, 1, imp::GRAY);
    img.at<int>(5, 5) = 5;
    std::cout << img.at<int>(5, 5) << std::endl;
    imp::JPEGDecoder decoder;
    decoder.open("./hui.jpg");
    return 0;
}
