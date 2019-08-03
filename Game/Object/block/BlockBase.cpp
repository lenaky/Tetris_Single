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
        auto& block_list = GetBlockList();
        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            if( true == itr->real_block_ )
            {
                GotoPosition( *itr );
                std::cout << " "; // ������ �����ϰ� 
            }                
        }

        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            itr->x_ = itr->x_ - 2;
        }
    }

    void BlockBase::OnMoveRight()
    {
        auto& block_list = GetBlockList();
        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            if( true == itr->real_block_ )
            {
                GotoPosition( *itr );
                std::cout << " "; // ������ �����ϰ� 
            }                
        }

        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            itr->x_ = itr->x_ + 2;
        }
    }

    void BlockBase::OnMoveDown()
    {
        for( auto& itr = _shape_position.begin(); itr != _shape_position.end(); itr++ )
        {
            if( true == itr->real_block_ )
            {
                GotoPosition( *itr );
                std::cout << " "; // ������ �����ϰ� 
            }
        }

        for( auto& itr = _shape_position.begin(); itr != _shape_position.end(); itr++ )
        {
            itr->y_ = itr->y_ + 1;
        }
    }

    void BlockBase::OnSpin()
    {
        auto& block_list = GetBlockList();
        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            if( true == itr->real_block_ )
            {
                GotoPosition( *itr );
                std::cout << " "; // ������ �����ϰ� 
            }
        }

        // �浹 �����۾�. ���ʿ� �پ�������, �����ʿ� �پ�������, �ٴڿ� �پ��������� ���� ��� �ʿ���
            
        std::vector<BLOCK> spined;

        for( int x = 0; x < _width; x++ )
        {
            for( int y = 0; y < _height; y++ )
            {
                auto& block_val = block_list[ (y + 1) * _height - (x + 1) ];
                spined.push_back( block_val );
            }
        } // ��ü �迭 90�� ȸ��. real_block ������ ����.

        for( int i = 0; i < block_list.size(); i++ )
        {
            block_list[ i ].real_block_ = false;
            block_list[ i ].real_block_ = spined[ i ].real_block_;
        } // real_block ���� ����

    }

    void BlockBase::_SetSize( int width, int height )
    {
        _width = width;
        _height = height;

        // �⺻ Ʋ�� �Է�
        for( int x = 0; x < _width; x++ )
        {
            for( int y = 0; y < _height; y++ )
            {
                BLOCK block( x * 2, y, false, GetBlockColor() );
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
}

