#ifndef _T_SHAPED_BLOCK_H_
#define _T_SHAPED_BLOCK_H_

#include "../GameObjectBase.h"
#include "BlockBase.h"

namespace TETRIS
{
    class TShapedBlock : public BlockBase
    {
    public:
        TShapedBlock( GameMapPtr const& map, BLOCK_COLOR color, char const* a_block_shape );
        virtual ~TShapedBlock() = default;
    };
}

#endif
