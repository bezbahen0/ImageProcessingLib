#include "include/imgcodec/MCU.hpp"

namespace imp
{
MCU::MCU()
{

}

MCU::MCU(const std::vector<std::vector<int>>& RLE, const std::vector<std::vector<Uint16>>& QTable) : QTable_(QTable)
{
    createMCU(RLE, QTable);
}

MCU::~MCU()
{
    QTable_.shrink_to_fit();
    //allMCU_.shrink_to_fit();
}

/*void MCU::add(std::vector<std::vector<int>>& RLE)
{
    createMCU(RLE, QTable_);
}*/

CompareMtrices& MCU::getAllMatrix()
{
    //return allMCU_;
    return block_;
}

void MCU::createMCU(const std::vector<std::vector<int>>& RLE, const std::vector<std::vector<Uint16>>& QTable)
{

}

}
