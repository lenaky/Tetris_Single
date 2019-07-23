#include "IShapedBlock.h"

namespace TETRIS 
{
    IShapedBlock::IShapedBlock( BLOCK_COLOR color, char const* a_block_shape ) : BlockBase( color, a_block_shape )
    {
        {
            BLOCK block( 2, 0, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 2, 1, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 2, 2, GetBlockColor() );
            AddBlock( block );
        }
        {
            BLOCK block( 2, 3, GetBlockColor() );
            AddBlock( block );
        }

    }

    void IShapedBlock::OnSpin()
    {
        auto& block_list = GetBlockList();
        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            GotoPosition( *itr );
            std::cout << " "; // ������ �����ϰ� 
        }

        // �浹 �����۾�. ���ʿ� �پ�������, �����ʿ� �پ�������, �ٴڿ� �پ�������.

        int xval = INT_MAX;
        int yval = INT_MAX;
        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            if( itr->x_ < xval )
            {
                xval = itr->x_;
            }

            if( itr->y_ < yval )
            {
                yval = itr->y_;
            }
        } // minimum ���� �����´�.
        
        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            itr->x_ = itr->x_ - xval;
            itr->y_ = itr->y_ - yval;
            // ���ذ� �߶󳻱�

            auto temp = itr->x_;
            itr->x_ = itr->y_ * 2;
            itr->y_ = temp / 2;
        }
        // �밢�� �̵�

        for( auto& itr = block_list.begin(); itr != block_list.end(); itr++ )
        {
            itr->x_ = itr->x_ + xval;        
            itr->y_ = itr->y_ + yval;
        }
        // x�ప ȸ��

    }
}