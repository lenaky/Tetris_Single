#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <memory>

#include "GameObjectBase.h"

/*

I :     бс
        бс
        бс
        бс

T :    бсбсбс
        бс

Rect : бсбс
       бсбс

Z :    бсбс
        бсбс

L :    бс
       бс
       бсбс

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

        }

        void OnMoveRight()
        {

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
