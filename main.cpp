#include <iostream>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sstream>
//#include "Game.h"

using namespace std;

int main()
{
    //Game gameObject;
    int row, col;
    noecho();

    initscr();
    char st[] = "Dette er en test!";
    getmaxyx(stdscr, row, col);
    WINDOW * top = newwin((row*2)/3, col, 0, 0);
    WINDOW * btm = newwin(((row*1)/3)-1, col, ((row*2)/3)+1 , 0);

    refresh();
    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_WHITE);


//    for(int i=0; i < 40; i++)
//    {
//        if(i%2 == 0) attron(A_BOLD | COLOR_PAIR(i%5));
//        mvwaddstr(top, i, i, row);
//        attroff(A_BOLD | COLOR_PAIR(i%5));
//        //getch();
//        sleep(1);
//        wrefresh(top);
//        //clear();
//    }


    //mvprintw(row/2, col, " rows and %d cols",row,col);
    mvwaddstr(top, 0, 0, st);
    box(top, 0, 0);
    mvwaddstr(btm, 0, 0, st);
    box(btm, 0, 0);
    mvwaddstr(btm,1,1,"Dette er en test, mohaha");
    stringstream ss;
    ss << row << " - " << col;
    string as = ss.str();
    mvwaddstr(btm,2,1,as.c_str());

    wrefresh(top);
    wrefresh(btm);

    getch();

    delwin(top);
    delwin(btm);

    endwin();
    return 0;
}
