#ifndef _RECT_SHAPED_BLOCK_H_
#define _RECT_SHAPED_BLOCK_H_

#include "../GameObjectBase.h"
#include "BlockBase.h"

namespace TETRIS
{
    class RectShapedBlock : public BlockBase
    {
    public:
        RectShapedBlock( GameMapPtr const& map, BLOCK_COLOR color, char const* a_block_shape );
        virtual ~RectShapedBlock() = default;
        virtual void OnSpin() override { }
    };
}

#endif
