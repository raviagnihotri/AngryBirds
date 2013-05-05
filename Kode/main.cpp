#include <iostream>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include "Game.h";

using namespace std;

int main()
{
    Game *game = new Game();
    delete game;

    return 0;

}
