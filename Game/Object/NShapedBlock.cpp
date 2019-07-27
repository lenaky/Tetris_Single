#include "NShapedBlock.h"

namespace TETRIS{

    NShapedBlock::NShapedBlock( BLOCK_COLOR color, char const* a_block_shape ) : BlockBase( color, a_block_shape )
    {
        _SetSize( 3, 3 );

        for( auto& itr : GetBlockList() )
        {
            if( itr.x_ == 0 && itr.y_ == 0 )
            {
                itr.real_block_ = true;
            }

            if( itr.x_ == 2 && itr.y_ == 0 )
            {
                itr.real_block_ = true;
            }

            if( itr.x_ == 2 && itr.y_ == 1 )
            {
                itr.real_block_ = true;
            }

            if( itr.x_ == 4 && itr.y_ == 1 )
            {
                itr.real_block_ = true;
            }
        }
    }
}