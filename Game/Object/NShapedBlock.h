#ifndef _N_SHAPED_BLOCK_H_
#define _N_SHAPED_BLOCK_H_

#include "GameObjectBase.h"
#include "BlockBase.h"

namespace TETRIS 
{
    class NShapedBlock : public BlockBase
    {
    public:
        NShapedBlock( BLOCK_COLOR color, char const* a_block_shape );
        virtual ~NShapedBlock() = default;

    };
}
#endif