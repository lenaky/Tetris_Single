#include <iostream>

#include "ConsoleKeyboardInput.h"

namespace TETRIS
{
    ConsoleKeyboardInput::~ConsoleKeyboardInput()
    {
        SetConsoleMode( _stdin_handle, _old_console_mode ); // restore console mode
    }

    ErrorCode ConsoleKeyboardInput::InitializeKeyboardInput()
    {
        _stdin_handle = GetStdHandle( STD_INPUT_HANDLE );
        if( _stdin_handle == INVALID_HANDLE_VALUE )
        {
            std::cout << "failed to GetStdHandle" << std::endl;
            return TETRIS_GET_HANDLE_FAILED;
        }

        if( !GetConsoleMode( _stdin_handle, &_old_console_mode ) )
        {
            std::cout << "failed to GetConsoleMode" << std::endl;
            return TETRIS_GET_CONSOLE_FAILED;
        }

        DWORD fdwMode = ENABLE_WINDOW_INPUT;
        if( !SetConsoleMode( _stdin_handle, fdwMode ) )
        {
            std::cout << "SetConsoleMode failed" << std::endl;
            return TETRIS_SET_CONSOLE_FAILED;
        }

        return TETRIS_ERROR_NONE;
    }

    /*
    void ConsoleKeyboardInput::ListenKeyboard( ConsoleKeyboardInput* instance )
    {
        DWORD cNumRead;
        INPUT_RECORD irInBuf[ 128 ];

        while( instance->GetRunState() )
        {
            if( !ReadConsoleInput(
                instance->GetHandle(),
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
                    instance->KeyEventProc( irInBuf[ i ].Event.KeyEvent );
                    break;
                }
            }
        }
    }
    */
}