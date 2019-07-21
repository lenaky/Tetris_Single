#include <iostream>
#include <chrono>

#include "GameManager.h"
#include "Util.hpp"
#include "Input/ConsoleKeyboardInput.h"
#include "Object/BlockConst.h"
#include "Object/ShapedBlockFatory.h"

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
                break;
            case VK_RIGHT:
                break;
            case VK_DOWN:
                GetWorkingBlock()->OnMoveDown();
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

        auto begin_tick = std::chrono::system_clock::now();

        int i = 0;
        while( _run )
        {
            if( i == 20 )
            {
                _current_working_block = nullptr;
                i = 0;
            }

            if( nullptr == GetWorkingBlock() )
            {
                auto rand_val = GetRandom( BLOCK_SHAPE_START, BLOCK_SHAPE_END );
                auto shaped_block = CreateGameBlock( rand_val );
                _current_working_block = shaped_block;
            }

            auto current_tick = std::chrono::system_clock::now();
            if( std::chrono::duration_cast< std::chrono::milliseconds >( current_tick - begin_tick ).count() > 1000 )
            {
                GetWorkingBlock()->OnMoveDown();
                GetWorkingBlock()->DrawObject();
                begin_tick = current_tick;
                i++;
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
                    break;
                }
            }
        }
    }
}