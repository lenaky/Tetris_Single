#ifndef _L_SHAPED_BLOCK_H_
#define _L_SHAPED_BLOCK_H_

#include "GameObjectBase.h"
#include "BlockBase.h"

namespace TETRIS
{
    class LShapedBlock : public BlockBase
    {
    public:
        LShapedBlock( BLOCK_COLOR color, char const* a_block_shape );
        virtual ~LShapedBlock() = default;

    };
}

#endif
