#include "NShapedBlock.h"

namespace TETRIS{

    NShapedBlock::NShapedBlock( BLOCK_COLOR color, char const* a_block_shape ) : BlockBase( color, a_block_shape )
    {
        {
            BLOCK block( 0, 0, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 2, 0, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 2, 1, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 4, 1, GetBlockColor() );
            AddBlock( block );
        }
    }

    void NShapedBlock::OnSpin()
    {

    }
}