#include "include/transform.hpp"

#include <cmath>

namespace imp
{

void idct(CompareMtrices& block, std::vector<std::array<std::array<float, 8>, 8>>& IDCTCoeffs)
{
    for(int i = 0; i < block.size(); ++i)
    {
        for(int y = 0; y < 8; ++y)
        {
            for(int x = 0; x < 8; ++x)
            {
                float sum = 0.0;
                
                for(int u = 0; u < 8; ++u)
                {
                    for( int v = 0; v < 8; ++v)
                    {
                        float Cu = u == 0 ? 1.0 / std::sqrt(2.0) : 1.0;
                        float Cv = v == 0 ? 1.0 / std::sqrt(2.0) : 1.0;
                        
                        sum += Cu * Cv * block[i][u][v] * std::cos( ( 2 * x + 1 ) * u * M_PI / 16.0 ) *
                                        std::cos( ( 2 * y + 1 ) * v * M_PI / 16.0 );
                    }
                }
                
                IDCTCoeffs[i][x][y] = 0.25 * sum;
            }
        }
    }
}

void convertYCbCrToRGB(CompareMtrices& block)
{
    for(int y = 0; y < 8; ++y)
    {
        for(int x = 0; x < 8; ++x)
        {
            float Y = block[0][y][x];
            float Cb = block[1][y][x];
            float Cr = block[2][y][x];

            int R = (int)std::floor( Y + 1.402 * ( 1.0 * Cr - 128.0 ) );
            int G = (int)std::floor( Y - 0.344136 * ( 1.0 * Cb - 128.0 ) - 0.714136 * ( 1.0 * Cr - 128.0 ) );
            int B = (int)std::floor( Y + 1.772 * ( 1.0 * Cb - 128.0 ) );
            
            R = std::max( 0, std::min( R, 255 ) );
            G = std::max( 0, std::min( G, 255 ) );
            B = std::max( 0, std::min( B, 255 ) );
            
            block[0][y][x] = R;
            block[1][y][x] = G;
            block[2][y][x] = B;
        }
    }

}

void performLevelShift(CompareMtrices& block, std::vector<std::array<std::array<float, 8>, 8>> IDCTCoeffs)
{
    for(auto i = 0; i < block.size(); ++i)
    {
        for(int y = 0; y < 8; ++y)
        {
            for(int x = 0; x < 8; ++x)
            {
                block[i][y][x] = std::roundl(IDCTCoeffs[i][y][x]) + 128;
            }
        }
    }

}

}
