#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Windows.h>
#include <iostream>
#include <vector>
#include <memory>

namespace TETRIS
{
    enum BLOCK_COLOR
    {
        BLOCK_COLOR_BLACK = 0,
        BLOCK_COLOR_BLUE,
        BLOCK_COLOR_GREEN,
        BLOCK_COLOR_CYAN,
        BLOCK_COLOR_RED,
        BLOCK_COLOR_MAGENTA,
        BLOCK_COLOR_BROWN,
        BLOCK_COLOR_LIGHTGRAY,
        BLOCK_COLOR_DARKGRAY,
        BLOCK_COLOR_LIGHTBLUE,
        BLOCK_COLOR_LIGHTGREEN,
        BLOCK_COLOR_LIGHTCYAN,
        BLOCK_COLOR_LIGHTRED,
        BLOCK_COLOR_LIGHTMAGENTA,
        BLOCK_COLOR_YELLOW,
        BLOCK_COLOR_WHITE
    };

    struct BLOCK
    {
        BLOCK( int x, int y, bool real_block, BLOCK_COLOR color ) : x_( x ), y_( y ), real_block_( real_block ), color_( color ) { }
        BLOCK( int x, int y, bool real_block, BLOCK_COLOR color, int factor ) : x_( x ), y_( y ), real_block_( real_block ), color_( color ), factor_( factor ) { }
        
        int x_ = 0;
        int y_ = 0;
        bool real_block_ = false;
        BLOCK_COLOR color_ = BLOCK_COLOR_BLACK;

        int factor_ = 0;
    };

    class GameObjectBase
    {
    public:
        GameObjectBase( char const* a_block_shape ) : _a_block_shape( a_block_shape )
        {

        }

        virtual ~GameObjectBase()
        {

        }

        void AddBlock( BLOCK const& pos )
        {
            _shape_position.push_back( pos );
        }

        void MergeBlock( GameObjectBase* target )
        {
            target->For_Each_Block( [ this ]( TETRIS::BLOCK& block ){
                if( true == block.real_block_ )
                {
                    _shape_position.push_back( block );
                }                
            } );            
        }

        virtual void DrawObject() const
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

        template <typename TFunc>
        void For_Each_Block( TFunc& func )
        {
            for( auto& item : _shape_position )
            {
                func( item );
            }
        }

        std::vector<BLOCK>& GetBlockList() { return _shape_position; }
        std::vector<BLOCK> const& GetBlockList() const { return _shape_position; }

    protected:
        
        void GotoPosition( BLOCK const& block ) const
        {
            COORD Cur;
            Cur.X = block.x_;
            Cur.Y = block.y_;
            SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), Cur );
        };

    protected:
        std::vector<BLOCK> _shape_position;
        char const* _a_block_shape = nullptr;
    };

    using GameObjectBasePtr = std::shared_ptr<GameObjectBase>;
}

#endif
