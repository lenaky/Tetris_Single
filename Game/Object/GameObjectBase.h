#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Windows.h>
#include <iostream>
#include <list>

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
        BLOCK( int x, int y, BLOCK_COLOR color ) : x_( x ), y_( y ), color_( color ) { }
        
        int x_ = 0;
        int y_ = 0;
        BLOCK_COLOR color_ = BLOCK_COLOR_BLACK;
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

        GameObjectBase& operator+( GameObjectBase& rhs )
        {
            for( auto itr = rhs._shape_position.begin(); itr != rhs._shape_position.end(); itr++ )
            {
                this->_shape_position.push_back( *itr );
            }

            return *this;
        }

        void DrawObject()
        {
            for( auto& itr = _shape_position.begin(); itr != _shape_position.end(); itr++)
            {
                GotoPosition( { itr->x_, itr->y_, itr->color_ } );
                std::cout << _a_block_shape << std::endl;
            }
        }

    protected:
        void AddBlock( BLOCK const& pos )
        {
            _shape_position.push_back( pos );
        }

        void GotoPosition( BLOCK const& block ) const
        {
            COORD Cur;
            Cur.X = block.x_;
            Cur.Y = block.y_;
            SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), Cur );
        };

        void OnBlockDown()
        {
            for( auto& itr = _shape_position.begin(); itr != _shape_position.end(); itr++ )
            {
                GotoPosition( *itr );
                std::cout << " "; // 기존거 삭제하고 
            }

            for( auto& itr = _shape_position.begin(); itr != _shape_position.end(); itr++ )
            {
                itr->y_ = itr->y_ + 1;
            }
        }

    private:
        std::list<BLOCK> _shape_position;
        char const* _a_block_shape = nullptr;
    };
}

#endif
