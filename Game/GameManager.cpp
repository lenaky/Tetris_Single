#include <iostream>
#include <chrono>
#include <sstream>

#include "GameManager.h"
#include "Util.hpp"
#include "Input/ConsoleKeyboardInput.h"
#include "Object/Block/BlockConst.h"
#include "Object/Block/ShapedBlockFatory.h"

namespace TETRIS
{
    GameManager::GameManager()
    {
        _input = new ConsoleKeyboardInput( this );
    }

    GameManager::~GameManager()
    {
        if( nullptr != _input )
        {
            delete _input;
        }
    }

    ErrorCode GameManager::Start()
    {
        auto result = _input->InitializeKeyboardInput();
        if( TETRIS_ERROR_NONE != result )
        {
            std::cout << "start failed. error=" << result;
            return result;
        }

        HANDLE consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo( consoleHandle, &info );

        _run = true;
        _game_thread = GAME_THREAD_PTR( new std::thread( std::bind( &GameManager::GameThread, this ) ) );

        return TETRIS_ERROR_NONE;
    }

    ErrorCode GameManager::Stop()
    {
        _run = false;
        return TETRIS_ERROR_NONE;
    }

    void GameManager::WaitForExit()
    {
        if( true == _game_thread->joinable() )
        {
            _game_thread->join();
        }
    }

    void GameManager::KeyEventProc( KEY_EVENT_RECORD ker )
    {
        if( ker.bKeyDown )
        {
            switch( ker.wVirtualKeyCode )
            {
            case VK_LEFT:
                if( false == GetWorkingBlock()->CheckCollision( MOVE_LEFT ) )
                {
                    GetWorkingBlock()->OnMoveLeft();
                    GetWorkingBlock()->DrawObject();
                }                
                break;
            case VK_RIGHT:
                if( false == GetWorkingBlock()->CheckCollision( MOVE_RIGHT ) )
                {
                    GetWorkingBlock()->OnMoveRight();
                    GetWorkingBlock()->DrawObject();
                }
                break;
            case VK_DOWN:
                if( false == GetWorkingBlock()->CheckCollision( MOVE_DOWN ) )
                {
                    GetWorkingBlock()->OnMoveDown();
                    GetWorkingBlock()->DrawObject();
                }                
                break;
            case VK_UP:
                GetWorkingBlock()->OnSpin();
                GetWorkingBlock()->DrawObject();
                break;
            case VK_SPACE:
                GetWorkingBlock()->OnPushBottom();
                GetWorkingBlock()->DrawObject();
                break;
            case VK_ESCAPE:
                Stop();
                std::cout << "game exit...." << std::endl;
                break;
            }
        }
    }

    void GameManager::GameThread()
    {
        DWORD cNumRead;
        INPUT_RECORD irInBuf[ 128 ];

        _game_map = GameMapPtr( new GameMapBase( { 12, 21 }, "﹥" ) );
        _game_map->DrawObject();

        AddScore( 0 );

        auto begin_tick = std::chrono::system_clock::now();

        while( _run )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
            if( nullptr == GetWorkingBlock() )
            {
                auto rand_val = GetRandom( BLOCK_SHAPE_START, BLOCK_SHAPE_END );
                auto shaped_block = CreateGameBlock( _game_map, rand_val );
                _current_working_block = shaped_block;

                if( true == _game_map->CheckGameEnd( _current_working_block.get() ) )
                {
                    exit( 0 );
                }

                GetWorkingBlock()->DrawObject();
            }

            auto current_tick = std::chrono::system_clock::now();
            if( std::chrono::duration_cast< std::chrono::milliseconds >( current_tick - begin_tick ).count() > 1000 )
            {
                if( false == _current_working_block->CheckCollision( MOVE_DOWN ) )
                {
                    GetWorkingBlock()->OnMoveDown();
                    GetWorkingBlock()->DrawObject();
                    begin_tick = current_tick;
                }
                else
                {
                    _game_map->MergeBlock( _current_working_block.get() );
                    AddScore( _game_map->ScoreBlocks() );
                    _game_map->DrawObject();
                    _current_working_block = nullptr;
                    begin_tick = current_tick;
                    continue;
                }                
            }

            DWORD numEvents = 0;
            GetNumberOfConsoleInputEvents( _input->GetHandle(), &numEvents );

            if( 0 >= numEvents )
            {
                continue;
            }

            if( !ReadConsoleInput(
                _input->GetHandle(),
                irInBuf,
                128,
                &cNumRead ) )
            {
                continue;
            }

            for( DWORD i = 0; i < cNumRead; i++ )
            {
                switch( irInBuf[ i ].EventType )
                {
                case KEY_EVENT:
                    KeyEventProc( irInBuf[ i ].Event.KeyEvent );
                    if( irInBuf[ i ].Event.KeyEvent.bKeyDown == TRUE && 
                        irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_SPACE )
                    {
                        _game_map->MergeBlock( _current_working_block.get() );
                        AddScore( _game_map->ScoreBlocks() );
                        _game_map->DrawObject();
                        _current_working_block = nullptr;
                        begin_tick = current_tick;
                    }
                    break;
                }
            }
        }
    }

    void GameManager::AddScore( std::int64_t add )
    {
        _game_score += add * 100;
        _RefreshScoreBoard();
    }

    void GameManager::_RefreshScoreBoard()
    {
        GotoPosition( 24, 0 );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), BLOCK_COLOR_WHITE );
        std::string str = "忙式式式式式式式式式式式式式式式式式式式式忖 ";
        std::cout << str << std::endl;
        GotoPosition( 24, 1 );
        str = "弛                    弛 ";
        std::cout << str << std::endl;
        GotoPosition( 24, 2 );
        str = "戌式式式式式式式式式式式式式式式式式式式式戎 ";
        std::cout << str << std::endl;       
        GotoPosition( 30, 1 );
        std::cout << "SCORE : " << _game_score << std::endl;
    }
}