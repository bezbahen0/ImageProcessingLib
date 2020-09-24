#ifndef MCU_HPP
#define MCU_HPP

#include "include/types.hpp"

namespace imp
{

class MCU
{
public:
    MCU();
    MCU(const std::vector<std::vector<int>>& RLE, const std::vector<std::vector<Uint16>>& QTable);
    ~MCU();

    //void add(std::vector<std::vector<int>>& RLE);
    CompareMtrices& getAllMatrix();

protected:
    void createMCU(const std::vector<std::vector<int>>& RLE, const std::vector<std::vector<Uint16>>& QTable);


    CompareMtrices block_;
    std::vector<std::vector<Uint16>> QTable_;
    //std::vector<MCU> allMCU_;
    static std::vector<int> DCDiff_;
    std::vector<std::array<std::array<float, 8>, 8>> IDCTCoeffs_;
};

}
#endif /* MCU_HPP */
