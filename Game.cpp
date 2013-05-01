#include <iostream>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sstream>

using namespace std;

int bird;
int target;
float gravity;

string logo[14];
logo[0] =  "    ______  __  __  ____    ____    __   __   ";
logo[1] = "   /\\  _  \\/\\ \\/\\ \\/\\  _`\\ /\\  _`\\ /\\ \\ /\\ \\ ";
logo[2] = "   \\ \\ \\L\\ \\ \\ `\\\\ \\ \\ \\L\\_\\ \\ \\L\\ \\`\\`\\\\/'/";
logo[3] = "    \\ \\  __ \\ \\ , ` \\ \\ \\L_L\\ \\ ,  /`\\ `\\ /'   ";
logo[4] = "     \\ \\ \\/\\ \\ \\ \\`\\ \\ \\ \\/, \\ \\ \\\ \\  `\\ \\ \\  ";
logo[5] = "      \\ \\_\\ \\_\\ \\_\\ \\_\\ \\____/\\ \\_\\ \\_\\ \\ \\_\\  ";
logo[6] = "       \\/_/\\/_/\\/_/\\/_/\\/___/  \\/_/\\/_/  \\/_/ ";
logo[7] = "         ____    ______   ____    ____    ____      n";
logo[8] = "        /\\  _`\\ /\\__  _\\ /\\  _`\\ /\\  _`\\ /\\  _`\\   ";
logo[9] = "        \\ \\ \\L\\ \\/_\/\\ \\/ \\ \\ \\L\\ \\ \\ \\/\\ \\ \\,\\L\\_\\  ";
logo[10] = "         \\ \\  _ <' \\ \\ \\  \\ \\ ,  /\\ \\ \\ \\ \\/_\\__ \\  ";
logo[11] = "          \\ \\ \\L\\ \\ \\_\\ \\__\\ \\ \\\\ \\\\ \\ \\_\\ \\/\\ \\L\\ \\ ";
logo[12] = "           \\ \\____/ /\\_____\\\\ \\_\\ \\_\\ \\____/\\ `\\____\\ ";
logo[13] = "            \\/___/  \\/_____/ \\/_/\\/ /\\/___/  \\/_____/ ";

Game::Game()
{
    initScreen();
    attron(COLOR_PAIR(6));

    box(top, 0, 0);

    mvwaddstr(btm, 0, 0, st);
    box(btm, 0, 0);

    welcomeScr();
    wrefresh(top);
    wrefresh(btm);

    userInput();

    delwin(top);
    delwin(btm);

    endwin();
}

void Game::initScreen()
{
    // Start ncurses
    initscr();

    int row, col, toprow, topcol, btmrow, btmcol;

    //Ikke tegn på skjermen ved brukerinput
    noecho();
    // Slå av cursor
    curs_set(0);
    //Keypad og function keys
    keypad(stdscr, TRUE);
    start_color();

    //Kalkuler størrelse på topp- og bunnvindu (3/4 og 1/4 av høyde)
    getmaxyx(stdscr, row, col);

    toprow = (row*3)/4;
    btmrow = ((row*1)/4)-1;
    btmcol = ((row*3)/4)+1;

    WINDOW * top = newwin(toprow, col, 0, 0);
    WINDOW * btm = newwin(btmrow, col, btmcol, 0);

    refresh();

    //Opprette noen fargepar
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);

}

void Game::welcomeScr()
{
    wattron(top, A_BOLD | COLOR_PAIR(1));

    //Printe ut logoen
    for(int i = 0; i < logo.size(); i++)
        mvwaddstr(top,i,1, logo[i].c_str());

    wattroff(top, A_BOLD);

    wattron(top, A_BOLD | COLOR_PAIR(6));

    //Printe ut menyen
    mvwaddstr(btm,0,1, "Meny");
    mvwaddstr(btm,1,1, "1. Start spill");
    mvwaddstr(btm,2,1, "2. Endre på noe");
    mvwaddstr(btm,3,1, "3. Hjelp");
    mvwaddstr(btm,4,1, "4. Avslutt");

    wrefresh(top);
    wrefresh(btm);

}

void Game::userInput()
{
    bool exit = false;

    while(true)
    {
        int in = getch();
        if(in == 1) //Nytt spill
        {
            wclear(btm);
            mvwaddstr(btm,0,1, "Select stage:");
            mvwaddstr(btm,1,1, "1 - The Earth");
            mvwaddstr(btm,2,1, "2 - The Moon");
            mvwaddstr(btm,3,1, "3 - Jupiter");
            mvwaddstr(btm,4,1, "3 - Abort");
            int in2 = getch();

            while(true)
            {
                int in2 = getch();
                if(in2 == 1)
                {
                    Stage stage = new Stage(1);
                    welcomeScr();
                    delete stage;
                    break;
                }
                else if(in2 == 2)
                {
                    Stage stage = new Stage(2);
                    welcomeScr();
                    delete stage;
                    break;
                }
                else if(in2 == 3)
                {
                    Stage stage = new Stage(3);
                    welcomeScr();
                    delete stage;
                    break;
                }
                else if(in2 == 4)
                {
                    break;
                }
            }
        }
        else if(in == 2) //Settings
        {
            // Settings?

        }
        else if(in == 3) //Hjelp
        {
            wclear(top);
            mvwaddstr(btm,1,1, "Her det kommer det litt hjelp");
            mvwaddstr(btm,2,1, "Dette er andre linje");
            mvwaddstr(btm,3,1, "Og tredje...");
            mvwaddstr(btm,4,1, "Til slutt den siste!");
            wrefresh(top);
            getch();
            welcomeScr();
            break;
        }
        else if(in == 4) //Avslutt
        {
            exit = true;
            break;
        }
    }
    if(!exit) userInput();
}

Game::~Game()
{
    //dtor
}
