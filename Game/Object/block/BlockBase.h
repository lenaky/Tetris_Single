#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <memory>

#include "../GameObjectBase.h"
#include "../map/GameMapBase.h"

namespace TETRIS 
{
    enum MOVE_TYPE
    {
        MOVE_LEFT = 0,
        MOVE_RIGHT = 1,
        MOVE_DOWN = 2,
        MOVE_BOTTOM = 3,
    };

    class BlockBase : public GameObjectBase
    {
    public:
        BlockBase( GameMapPtr const& map, BLOCK_COLOR color, char const* a_block_shape );
        virtual ~BlockBase() = default;

        BLOCK_COLOR GetBlockColor() const { return _color; }

        bool CheckCollision( MOVE_TYPE type );
        void OnMoveLeft();
        void OnMoveRight();
        void OnMoveDown();
        virtual void OnSpin();

        GameMapPtr const& GetMap() const { return _map_ref; }

    protected:
        void _SetSize( int width, int height );
        void _AdjustStartPosition();

    private:
        BLOCK_COLOR _color = BLOCK_COLOR_BLACK;
        int _width = 0;
        int _height = 0;
        GameMapPtr const& _map_ref = nullptr;
    };

    using BlockBasePtr = std::shared_ptr<BlockBase>;
}

#endif