#include "include/imgcodec/MCU.hpp"
#include "include/imgcodec/utils.hpp"
#include "include/transform.hpp"

namespace imp
{
std::vector<int> MCU::DCDiff_ = {};

MCU::MCU()
{

}

MCU::MCU(const std::vector<std::vector<int>>& RLE, const std::vector<std::vector<Uint16>>& QTable) : QTable_(QTable)
{
    if(DCDiff_.empty())
    {
        DCDiff_ = std::vector<int>(RLE.size());
        std::fill(DCDiff_.begin(), DCDiff_.end(), 0);
    }
    IDCTCoeffs_ = std::vector<std::array<std::array<float, 8>, 8>>(RLE.size());
    block_ = CompareMtrices(RLE.size());

    createMCU(RLE, QTable);
}

MCU::~MCU()
{
    QTable_.shrink_to_fit();
}

CompareMtrices& MCU::getAllMatrix()
{
    return block_;
}

void MCU::createMCU(const std::vector<std::vector<int>>& RLE, const std::vector<std::vector<Uint16>>& QTable)
{
    for ( int compID = 0; compID < RLE.size(); compID++ )
    {
        std::array<int, 64> zzOrder;            
        std::fill( zzOrder.begin(), zzOrder.end(), 0 );
        int j = -1;
        
        for ( auto i = 0; i <= RLE[compID].size() - 2; i += 2 )
        {
            if ( RLE[compID][i] == 0 && RLE[compID][i + 1] == 0 )
                break;
            
            j += RLE[compID][i] + 1;
            zzOrder[j] = RLE[compID][i + 1];
        }
        
        DCDiff_[compID] += zzOrder[0];
        zzOrder[0] = DCDiff_[compID];
        
        int QIndex = compID == 0 ? 0 : 1;
        for ( auto i = 0; i < 64; ++i ) 
            zzOrder[i] *= QTable_[QIndex][i];
        
        for ( auto i = 0; i < 64; ++i )
        {
            auto coords = utils::zzOrderToMatIndices(i);
            
            block_[compID][coords.first][coords.second] = zzOrder[i];
        }
    }
    
    idct(block_, IDCTCoeffs_);
    performLevelShift(block_, IDCTCoeffs_);
    if(RLE.size() == RGB)
    {
        convertYCbCrToRGB(block_);
    }
}

}
