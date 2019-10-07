#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <memory>
#include <thread>
#include <atomic>

#include "ErrorDefine.h"
#include "Input/ConsoleKeyboardInput.h"
#include "Object/map/GameMapBase.h"
#include "Object/Block/BlockBase.h"

namespace TETRIS
{
    class GameManager
    {
    public:
        using GAME_THREAD_PTR = std::shared_ptr<std::thread>;
    public:
        GameManager();
        ~GameManager();

        ErrorCode Start();
        ErrorCode Stop();

        void WaitForExit();

        void GameThread();

        void KeyEventProc( KEY_EVENT_RECORD ker );

        BlockBasePtr const& GetWorkingBlock() const
        {
            return _current_working_block;
        }

        void AddScore( std::int64_t add );

    private:
        void GotoPosition( int x, int y ) const
        {
            COORD Cur;
            Cur.X = x;
            Cur.Y = y;
            SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), Cur );
        };

        void _RefreshScoreBoard();

    private :

        std::atomic<bool> _run = false;
        ConsoleKeyboardInput* _input = nullptr;
        GAME_THREAD_PTR _game_thread = nullptr;

        BlockBasePtr _current_working_block = nullptr;
        GameMapPtr  _game_map = nullptr;

        std::int64_t _game_score = 0;

    };
}

#endif
