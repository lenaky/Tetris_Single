#include "IShapedBlock.h"

namespace TETRIS 
{
    IShapedBlock::IShapedBlock( BLOCK_COLOR color, char const* a_block_shape ) : BlockBase( color, a_block_shape )
    {
        {
            BLOCK block( 2, 0, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 2, 1, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 2, 2, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 2, 3, GetBlockColor() );
            AddBlock( block );
        }

    }

    void IShapedBlock::OnSpin()
    {

    }
}