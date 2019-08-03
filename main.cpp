#include <iostream>

#include "Game/GameManager.h"

int main()
{
    TETRIS::GameManager game;

    game.Start();

    game.WaitForExit();

    system( "pause" );

    return 0;
}