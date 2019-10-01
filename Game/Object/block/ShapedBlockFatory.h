#ifndef _SHAPED_BLOCK_FACTORY_H_
#define _SHAPED_BLOCK_FACTORY_H_

#include <memory>

#include "../map/GameMapBase.h"
#include "BlockConst.h"
#include "IShapedBlock.h"
#include "LShapedBlock.h"
#include "RevLShapedBlock.h"
#include "NShapedBlock.h"
#include "RevNShapedBlock.h"
#include "RectShapedBlock.h"
#include "TShapedBlock.h"

namespace TETRIS
{
    static BlockBasePtr CreateGameBlock( GameMapPtr const& map, std::int64_t random_value )
    {
        switch( random_value )
        {
        case TETRIS::BLOCK_SHAPE_I:
            {
                return std::shared_ptr<TETRIS::IShapedBlock>( new TETRIS::IShapedBlock( map, TETRIS::BLOCK_COLOR_RED, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_L:
            {
                return std::shared_ptr<TETRIS::LShapedBlock>( new TETRIS::LShapedBlock( map, TETRIS::BLOCK_COLOR_YELLOW, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_REV_L:
            {
                return std::shared_ptr<TETRIS::RevLShapedBlock>( new TETRIS::RevLShapedBlock( map, TETRIS::BLOCK_COLOR_CYAN, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_N:
            {
                return std::shared_ptr<TETRIS::NShapedBlock>( new TETRIS::NShapedBlock( map, TETRIS::BLOCK_COLOR_BROWN, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_REV_N:
            {
                return std::shared_ptr<TETRIS::RevNShapedBlock>( new TETRIS::RevNShapedBlock( map, TETRIS::BLOCK_COLOR_LIGHTMAGENTA, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_RECT:
            {
                return std::shared_ptr<TETRIS::RectShapedBlock>( new TETRIS::RectShapedBlock( map, TETRIS::BLOCK_COLOR_LIGHTBLUE, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_T:
            {
                return std::shared_ptr<TETRIS::TShapedBlock>( new TETRIS::TShapedBlock( map, TETRIS::BLOCK_COLOR_GREEN, "бс" ) );
            }
        default:
            {
                return std::shared_ptr<TETRIS::IShapedBlock>( new TETRIS::IShapedBlock( map, TETRIS::BLOCK_COLOR_RED, "бс" ) );
            }
        }

        return nullptr;
    }
}

#endif
