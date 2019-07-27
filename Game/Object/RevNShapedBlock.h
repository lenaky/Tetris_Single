#ifndef _REV_N_SHAPED_BLOCK_H_
#define _REV_N_SHAPED_BLOCK_H_

#include "GameObjectBase.h"
#include "BlockBase.h"

namespace TETRIS 
{
    class RevNShapedBlock : public BlockBase
    {
    public:
        RevNShapedBlock( BLOCK_COLOR color, char const* a_block_shape );
        virtual ~RevNShapedBlock() = default;

    };
}
#endif