#include "BlockBase.h"

namespace TETRIS 
{
    BlockBase::BlockBase( GameMapPtr const& map, BLOCK_COLOR color, char const* a_block_shape ) : GameObjectBase( a_block_shape ), _map_ref( map ), _color( color )
    {
        int block_color = color + BLOCK_COLOR_BLACK * 16;
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), block_color );
    }

    bool BlockBase::CheckCollision( MOVE_TYPE type )
    {
        bool collision = false;
        GetMap()->For_Each_Block( [ &collision, type, this ]( TETRIS::BLOCK& block ) {

            switch( type )
            {
            case MOVE_LEFT:
                {
                    for( auto const& my_block : _shape_position )
                    {
                        if( block.y_ == my_block.y_ && true == my_block.real_block_)
                        {
                            if( ( block.x_ ) == ( my_block.x_ - 2 ) )
                            {
                                collision = true;
                                break;
                            }
                        }
                    }
                    break;
                }
            case MOVE_RIGHT:
                {
                    for( auto const& my_block : _shape_position )
                    {
                        if( block.y_ == my_block.y_ && true == my_block.real_block_ )
                        {
                            if( ( block.x_ ) == ( my_block.x_ + 2 ) )
                            {
                                collision = true;
                                break;
                            }
                        }
                    }
                    break;
                }
            case MOVE_DOWN:
                {
                    for( auto const& my_block : _shape_position )
                    {
                        if( block.y_ == my_block.y_ + 1 && true == my_block.real_block_ )
                        {
                            if( block.x_ == my_block.x_ )
                            {
                                collision = true;
                                break;
                            }                            
                        }
                    }
                    break;
                }
            case MOVE_BOTTOM:
                {

                    break;
                }
            }
        } );

        return collision;
    }
        
    void BlockBase::OnMoveLeft()
    {
        _ClearPreviousBlockList();

        auto& block_list = GetBlockList();

        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            itr->x_ = itr->x_ - 2;
        }
    }

    void BlockBase::OnMoveRight()
    {
        _ClearPreviousBlockList();

        auto& block_list = GetBlockList();

        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            itr->x_ = itr->x_ + 2;
        }
    }

    void BlockBase::OnMoveDown()
    {
        _ClearPreviousBlockList();

        auto& block_list = GetBlockList();

        for( auto& itr = _shape_position.begin(); itr != _shape_position.end(); itr++ )
        {
            itr->y_ = itr->y_ + 1;
        }
    }

    void BlockBase::OnPushBottom()
    {
        _ClearPreviousBlockList();

        auto& block_list = GetBlockList();
        int collision_factor = 0;

        while( false == GetMap()->CheckMapCollision( block_list, collision_factor ) )
        {
            for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
            {
                itr->y_ = itr->y_ + 1;
            }
        }

        CorrectBlocks( block_list, MAP_FACTOR_BOTTOMLINE );
    }

    void BlockBase::OnSpin()
    {
        _ClearPreviousBlockList();

        auto& block_list = GetBlockList();

        // 충돌 보정작업. 왼쪽에 붙어있을때, 오른쪽에 붙어있을때, 바닥에 붙어있을때에 대한 계산 필요함

        std::vector<BLOCK> spined;

        for( int x = 0; x < _width; x++ )
        {
            for( int y = 0; y < _height; y++ )
            {
                auto& block_val = block_list[ ( y + 1 ) * _height - ( x + 1 ) ];
                spined.push_back( block_val );
            }
        } // 전체 배열 90도 회전. real_block 정보만 얻어간다.


        std::vector<BLOCK> tmp_block_list( block_list );

        for( int i = 0; i < tmp_block_list.size(); i++ )
        {
            tmp_block_list[ i ].real_block_ = false;
            tmp_block_list[ i ].real_block_ = spined[ i ].real_block_;
        } // real_block 정보 갱신

        int collision_factor = 0;
        bool swap = true;

        while( true == GetMap()->CheckMapCollision( tmp_block_list, collision_factor ) )
        {
            CorrectBlocks( tmp_block_list, collision_factor );
            if( MAP_FACTOR_INSIDE == collision_factor )
            {
                swap = false;
                break;
            }
        }

        if( swap )
        {
            block_list.swap( tmp_block_list );
        }        
    }

    void BlockBase::_SetSize( int width, int height )
    {
        _width = width;
        _height = height;

        // 기본 틀값 입력
        for( int x = 0; x < _width; x++ )
        {
            for( int y = 0; y < _height; y++ )
            {
                BLOCK block( x * 2, y, false, GetBlockColor(), MAP_FACTOR_INSIDE );
                AddBlock( block );
            }
        }
    }

    void BlockBase::_AdjustStartPosition()
    {
        int offset = 0;
        offset = GetMap()->GetMapSize().width_ / 2;
        For_Each_Block( [ offset ]( TETRIS::BLOCK& block ){
            block.x_ += offset;
        } );
    }

    void BlockBase::_ClearPreviousBlockList()
    {
        auto& block_list = GetBlockList();
        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            if( true == itr->real_block_ )
            {
                GotoPosition( *itr );
                std::cout << " "; // 기존거 삭제하고 
            }
        }
    }

    void BlockBase::CorrectBlocks( OUT std::vector<BLOCK>& blocks, int collision_factor )
    {
        if( collision_factor & MAP_FACTOR_INSIDE ) // 다른 블록때문에 걸리는 경우는 무시하자.
        {
            return;
        }

        if( collision_factor & MAP_FACTOR_LEFTLINE )
        {
            for( auto& block : blocks )
            {
                block.x_ = block.x_ + 2;
            }
        }

        if( collision_factor & MAP_FACTOR_RIGHTLINE )
        {
            for( auto& block : blocks )
            {
                block.x_ = block.x_ - 2;
            }
        }

        if( collision_factor & MAP_FACTOR_BOTTOMLINE )
        {
            for( auto& block : blocks )
            {
                block.y_ = block.y_ - 1;
            }
        }
    }
}

