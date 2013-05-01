#include <iostream>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include "Game.h";


using namespace std;

int main()
{
    Game game = new Game();
    delete game;

    return 0;

}

//    string bird1 = "     /^``^\\";
//    string bird2 = "   \\/   \\_/\\";
//    string bird3 = "  --1 .  00|";
//    string bird4 = "   /1    ->|";
//    string bird5 = "     \\_____/";
