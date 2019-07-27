#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <memory>

#include "GameObjectBase.h"

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
                std::cout << " "; // ������ �����ϰ� 
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
                std::cout << " "; // ������ �����ϰ� 
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

        virtual void OnSpin()
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
    protected:
        void _SetSize( int width, int height )
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

    private:
        BLOCK_COLOR _color = BLOCK_COLOR_BLACK;
        int _width = 0;
        int _height = 0;
    };

    using BlockBasePtr = std::shared_ptr<BlockBase>;
}

#endif
