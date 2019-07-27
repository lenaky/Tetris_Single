#include "IShapedBlock.h"

namespace TETRIS 
{
    IShapedBlock::IShapedBlock( BLOCK_COLOR color, char const* a_block_shape ) : BlockBase( color, a_block_shape )
    {
        _SetSize( 4, 4 );

        for( auto& itr : GetBlockList() )
        {
            if( itr.x_ == 2 && itr.y_ == 0 )
            {
                itr.real_block_ = true;
            }

            if( itr.x_ == 2 && itr.y_ == 1 )
            {
                itr.real_block_ = true;
            }

            if( itr.x_ == 2 && itr.y_ == 2 )
            {
                itr.real_block_ = true;
            }

            if( itr.x_ == 2 && itr.y_ == 3 )
            {
                itr.real_block_ = true;
            }
        }
    }
}