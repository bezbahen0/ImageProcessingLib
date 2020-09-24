#include "include/imgcodec/JPEGDecoder.hpp"
#include "include/loadsave.hpp"

int main(int argc, char* argv[])
{
    imp::Mat mat = imp::imread(argv[1]);
    imp::imwrite(argv[2], mat);
    return 0;
}
