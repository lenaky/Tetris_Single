#include "LShapedBlock.h"

namespace TETRIS
{
    LShapedBlock::LShapedBlock( BLOCK_COLOR color, char const* a_block_shape ) : BlockBase( color, a_block_shape )
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
            BLOCK block( 4, 2, GetBlockColor() );
            AddBlock( block );
        }
    }

    void LShapedBlock::OnSpin()
    {

    }
}