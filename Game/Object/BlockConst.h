#ifndef _BLOCK_CONST_H_
#define _BLOCK_CONST_H_

namespace TETRIS 
{
    enum BLOCK_SHAPE : int
    {
        BLOCK_SHAPE_START      = 0,
        BLOCK_SHAPE_I          = BLOCK_SHAPE_START,
        BLOCK_SHAPE_T          = 1,
        BLOCK_SHAPE_RECT       = 2,
        BLOCK_SHAPE_L          = 3,
        BLOCK_SHAPE_N          = 4,
        BLOCK_SHAPE_END        = BLOCK_SHAPE_N,
    };
}
#endif
