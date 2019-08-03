#include "GameMapBase.h"

namespace TETRIS 
{
    GameMapBase::GameMapBase( MapSize map_size, char const* a_block_shape ) : GameObjectBase( a_block_shape ), _map_size( map_size )
    {
        for( int y = 0; y < _map_size.height_; y++ )
        {
            for( int x = 0; x < _map_size.width_ * 2; x += 2 )
            {
                if( ( _map_size.height_ - 1 ) == y )
                {
                    AddBlock( BLOCK( x, y, true, BLOCK_COLOR_WHITE ) );
                }
                else 
                {
                    if( 0 == x || ( _map_size.width_ * 2 - 2 ) == x )
                    {
                        AddBlock( BLOCK( x, y, true, BLOCK_COLOR_WHITE ) );
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

}