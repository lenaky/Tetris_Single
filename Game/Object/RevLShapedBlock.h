#ifndef _REV_L_SHAPED_BLOCK_H_
#define _REV_L_SHAPED_BLOCK_H_

#include "GameObjectBase.h"
#include "BlockBase.h"

namespace TETRIS
{
    class RevLShapedBlock : public BlockBase
    {
    public:
        RevLShapedBlock( BLOCK_COLOR color, char const* a_block_shape );
        virtual ~RevLShapedBlock() = default;

    };
}

#endif
