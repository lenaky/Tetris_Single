#include "GameMapBase.h"

namespace TETRIS 
{
    GameMapBase::GameMapBase( MapSize map_size, char const* a_block_shape ) : GameObjectBase( a_block_shape ), _map_size( map_size )
    {
        for( int y = 0; y < _map_size.height_; y++ )
        {
            for( int x = 0; x < _map_size.width_ * 2; x += 2 )
            {
                enum MapFactor factor = MAP_FACTOR_NONE;

                if( ( _map_size.height_ - 1 ) == y ) // ¸Ç ¹Ø
                {
                    factor = MAP_FACTOR_BOTTOMLINE;
                    AddBlock( BLOCK( x, y, true, BLOCK_COLOR_WHITE, factor ) );
                }
                else 
                {
                    if( 0 == x || ( _map_size.width_ * 2 - 2 ) == x )
                    {
                        if( 0 == x )
                        {
                            factor = MAP_FACTOR_LEFTLINE;
                        }
                        else
                        {
                            factor = MAP_FACTOR_RIGHTLINE;
                        }

                        AddBlock( BLOCK( x, y, true, BLOCK_COLOR_WHITE, factor ) );
                    }
                }
            }
        }
    }

    void GameMapBase::DrawObject() const
    {
        for( auto& itr = _shape_position.begin(); itr != _shape_position.end(); itr++ )
        {
            if( true == itr->real_block_ )
            {
                GotoPosition( *itr );
                std::cout << _a_block_shape << std::endl;
            }
        }
    }

    bool GameMapBase::CheckMapCollision( std::vector<BLOCK> const& blocks, OUT int& collision_factor )
    {
        collision_factor = 0;

        for( auto const& block : _shape_position )
        {
            for( int i = 0; i < blocks.size(); i++ )
            {
                if( blocks[ i ].x_ == block.x_ &&
                    blocks[ i ].y_ == block.y_ &&
                    true == blocks[ i ].real_block_ )
                {
                    collision_factor |= block.factor_;
                }
            }
        }

        return collision_factor == 0 ? false : true;
    }

}