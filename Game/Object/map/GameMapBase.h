#ifndef _GAME_MAP_BASE_H_
#define _GAME_MAP_BASE_H_

#include <memory>
#include "../GameObjectBase.h"

namespace TETRIS
{
    enum MapFactor : int
    {
        MAP_FACTOR_NONE         = 0,
        MAP_FACTOR_LEFTLINE     = 1 << 0,
        MAP_FACTOR_RIGHTLINE    = 1 << 1 ,
        MAP_FACTOR_BOTTOMLINE   = 1 << 2 ,
        MAP_FACTOR_INSIDE       = 1 << 3 ,
    };

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

        bool CheckMapCollision( std::vector<BLOCK> const& blocks, OUT int& collision_factor );

    private:
        MapSize _map_size;

    };

    using GameMapPtr = std::shared_ptr<GameMapBase>;
}

#endif
