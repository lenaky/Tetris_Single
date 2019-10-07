#include "GameMapBase.h"
#include <set>

namespace TETRIS 
{
    GameMapBase::GameMapBase( MapSize map_size, char const* a_block_shape ) : GameObjectBase( a_block_shape ), _map_size( map_size )
    {
        for( int y = 0; y < _map_size.height_; y++ )
        {
            for( int x = 0; x < _map_size.width_ * 2; x += 2 )
            {
                enum MapFactor factor = MAP_FACTOR_NONE;

                if( ( _map_size.height_ - 1 ) == y ) // 맨 밑
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
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), itr->color_ );
                std::cout << _a_block_shape << std::endl;
            }
        }
    }

    std::int64_t GameMapBase::ScoreBlocks()
    {
        std::set<int> yvalues;

        for( int y = 0; y < _map_size.height_ - 1; y++ )
        {
            int x_size = (_map_size.width_ * 2 - 4) / 2; // width 길이 전체 블록 개수
            for( int x = 2; x <= ( _map_size.width_ * 2 - 4 ); x = x + 2 )
            {
                For_Each_Block( [&x_size, &yvalues, x, y]( BLOCK const& block ) {

                    if( true == block.real_block_ )
                    {
                        if( block.x_ == x && block.y_ == y )
                        {
                            x_size--;
                        }
                    }
                } );
            }

            if( 0 == x_size )
            {
                yvalues.insert( y );
            }            
        }

        _SinkBlocks( yvalues );

        return yvalues.size();
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

    void GameMapBase::_SinkBlocks( std::set<int> const& yvalues )
    {
        if( 0 == yvalues.size() )
        {
            return;
        }

        auto& blocks = GetBlockList();

        for( auto target_yvalue : yvalues )
        {
            for( auto& block_itr = blocks.begin(); block_itr != blocks.end(); )
            {
                if( MAP_FACTOR_INSIDE == block_itr->factor_ )
                {
                    // 같은 y 높이에 있는 블럭들은 삭제한다.
                    if( target_yvalue == block_itr->y_ )
                    {
                        GotoPosition( *block_itr );
                        std::cout << " "; // 그려진 것 삭제

                        block_itr = blocks.erase( block_itr );
                        continue;
                    }
                }

                block_itr = block_itr + 1;
            } 

            for( int move_down_block = target_yvalue - 1; move_down_block > 0; move_down_block-- )
            {
                for( auto& block_itr = blocks.begin(); block_itr != blocks.end(); )
                {
                    if( MAP_FACTOR_INSIDE == block_itr->factor_ )
                    {
                        if (block_itr->y_ == move_down_block )
                        {
                            GotoPosition( *block_itr );
                            std::cout << " "; // 위에 그려진 것들 삭제
                            block_itr->y_ = block_itr->y_ + 1;
                        }
                    }

                    block_itr = block_itr + 1;
                } // 블록 한칸씩 아래로 내림
            } 
        }        
    }

    bool GameMapBase::CheckGameEnd( GameObjectBase* target ) const
    {
        bool collision = false;
        auto const& blocks = GetBlockList();

        target->For_Each_Block( [ &blocks, &collision ]( BLOCK& target_each_block ) {
            for( auto const& block : blocks )
            {
                if( target_each_block.x_ == block.x_ &&
                    target_each_block.y_ == block.y_ &&
                    target_each_block.real_block_ == true )
                {
                    collision = true;
                }
            }
        } );       

        return collision == true ? true : false;
    }
}