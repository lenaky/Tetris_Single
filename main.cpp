#include <iostream>

#include "Game/GameManager.h"

#include "Game/Object/IShapedBlock.h"
#include "Game/Object/LShapedBlock.h"
#include "Game/Object/NShapedBlock.h"
#include "Game/Object/RectShapedBlock.h"
#include "Game/Object/TShapedBlock.h"

int main()
{
    TETRIS::GameManager game;

    game.Start();

    game.WaitForExit();

    system( "pause" );

    return 0;
}