#ifndef _SHAPED_BLOCK_FACTORY_H_
#define _SHAPED_BLOCK_FACTORY_H_

#include <memory>

#include "BlockConst.h"
#include "IShapedBlock.h"
#include "LShapedBlock.h"
#include "NShapedBlock.h"
#include "RectShapedBlock.h"
#include "TShapedBlock.h"

namespace TETRIS
{
    static BlockBasePtr CreateGameBlock( std::int64_t random_value )
    {
        switch( random_value )
        {
        case TETRIS::BLOCK_SHAPE_I:
            {
                return std::shared_ptr<TETRIS::IShapedBlock>( new TETRIS::IShapedBlock( TETRIS::BLOCK_COLOR_RED, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_L:
            {
                return std::shared_ptr<TETRIS::LShapedBlock>( new TETRIS::LShapedBlock( TETRIS::BLOCK_COLOR_YELLOW, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_N:
            {
                return std::shared_ptr<TETRIS::NShapedBlock>( new TETRIS::NShapedBlock( TETRIS::BLOCK_COLOR_BROWN, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_RECT:
            {
                return std::shared_ptr<TETRIS::RectShapedBlock>( new TETRIS::RectShapedBlock( TETRIS::BLOCK_COLOR_BLUE, "бс" ) );
            }
        case TETRIS::BLOCK_SHAPE_T:
            {
                return std::shared_ptr<TETRIS::TShapedBlock>( new TETRIS::TShapedBlock( TETRIS::BLOCK_COLOR_GREEN, "бс" ) );
            }
        default:
            {
                return std::shared_ptr<TETRIS::IShapedBlock>( new TETRIS::IShapedBlock( TETRIS::BLOCK_COLOR_RED, "бс" ) );
            }
        }

        return nullptr;
    }
}

#endif
