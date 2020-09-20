#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "types.hpp"

namespace imp
{
    void idct(CompareMtrices& block, std::vector<std::array<std::array<float, 8>, 8>>& IDCTCoeffs); 
    void convertYCbCrToRGB(CompareMtrices& block);
    void performLevelShift(CompareMtrices& block, std::vector<std::array<std::array<float, 8>, 8>> IDCTCoeffs);
}

#endif /* TRANSFORM_HPP */
