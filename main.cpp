#include <iostream>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include "Game.h";
#include <curses.h>

using namespace std;

int main()
{
    initscr();
    int row, col;
    getmaxyx(stdscr, row, col);

    if(row < 40 || col < 130)
    {
        endwin();
        cout << "Terminalstørrelsen er for liten! Vennligst øk størrelsen til minimum 130x40." << endl;
    }
    else
    {
        Game *game = new Game();
        delete game;
        endwin();
    }

    return 0;

}
