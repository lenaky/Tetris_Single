#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <memory>

#include "GameObjectBase.h"

/*

I :     ■
        ■
        ■
        ■

T :    ■■■
        ■

Rect : ■■
       ■■

Z :    ■■
        ■■

L :    ■
       ■
       ■■

*/

namespace TETRIS 
{
    class BlockBase : public GameObjectBase
    {
    public:
        BlockBase( BLOCK_COLOR color, char const* a_block_shape ) : GameObjectBase( a_block_shape ), _color( color )
        {
            int block_color = color + BLOCK_COLOR_BLACK * 16;
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), block_color );
        }
        virtual ~BlockBase() = default;

        BLOCK_COLOR GetBlockColor() const { return _color; }
        
        void OnMoveLeft()
        {
            auto& block_list = GetBlockList();
            for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
            {
                GotoPosition( *itr );
                std::cout << " "; // 기존거 삭제하고 
            }

            for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
            {
                itr->x_ = itr->x_ - 2;
            }
        }

        void OnMoveRight()
        {
            auto& block_list = GetBlockList();
            for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
            {
                GotoPosition( *itr );
                std::cout << " "; // 기존거 삭제하고 
            }

            for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
            {
                itr->x_ = itr->x_ + 2;
            }
        }

        void OnMoveDown()
        {
            OnBlockDown();
        }

        virtual void OnSpin() = 0;

    private:
        BLOCK_COLOR _color = BLOCK_COLOR_BLACK;
    };

    using BlockBasePtr = std::shared_ptr<BlockBase>;
}

#endif
