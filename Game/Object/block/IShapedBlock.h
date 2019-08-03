#ifndef _I_SHAPED_BLOCK_H_
#define _I_SHAPED_BLOCK_H_

#include "BlockBase.h"
#include "../GameObjectBase.h"

namespace TETRIS
{
    class IShapedBlock : public BlockBase
    {
    public:
        IShapedBlock( GameMapPtr const& map, BLOCK_COLOR color, char const* a_block_shape );
        virtual ~IShapedBlock() = default;
    };
}
#endif
