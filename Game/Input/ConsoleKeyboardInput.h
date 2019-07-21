#ifndef _CONSOLE_KEYBOARD_INPUT_H_
#define _CONSOLE_KEYBOARD_INPUT_H_

#include <Windows.h>

#include "../ErrorDefine.h"

namespace TETRIS {
    class GameManager;
    class ConsoleKeyboardInput
    {
    public:
        ConsoleKeyboardInput() = delete;
        ConsoleKeyboardInput( GameManager* manager ) :_game_manager( manager ) { }
        ~ConsoleKeyboardInput();

        ErrorCode InitializeKeyboardInput();

        HANDLE const& GetHandle() const
        {
            return _stdin_handle;
        }

    private:
        HANDLE _stdin_handle = nullptr;
        DWORD _old_console_mode;

        GameManager* _game_manager = nullptr;
    };
}

#endif