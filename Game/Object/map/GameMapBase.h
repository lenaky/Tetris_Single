#ifndef _GAME_MAP_BASE_H_
#define _GAME_MAP_BASE_H_

#include <memory>
#include "../GameObjectBase.h"

namespace TETRIS
{
    struct MapSize
    {
        MapSize( int width, int height ) : width_( width ), height_( height ) { }
        int width_ = 0;
        int height_ = 0;
    };

    class GameMapBase : public GameObjectBase
    {
    public:
        GameMapBase( MapSize map_size, char const* a_block_shape );
        virtual ~GameMapBase() { }
        
        virtual void DrawObject() const override;

        MapSize const& GetMapSize() const
        {
            return _map_size;
        }

    private:
        MapSize _map_size;

    };

    using GameMapPtr = std::shared_ptr<GameMapBase>;
}

#endif
