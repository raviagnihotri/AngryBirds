#include <iostream>
#include "Game.h"
#include "Stage.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sstream>

using namespace std;

int bird;
int target;
float gravity;

WINDOW * top;
WINDOW * btm;
int toprow;

vector<string> logo(14);
vector<string> sun(5);

void Game::initLogo()
{
    logo[0] =  "    ______  __  __  ____    ____    __   __   ";
    logo[1] = "   /\\  _  \\/\\ \\/\\ \\/\\  _`\\ /\\  _`\\ /\\ \\ /\\ \\ ";
    logo[2] = "   \\ \\ \\L\\ \\ \\ `\\\\ \\ \\ \\L\\_\\ \\ \\L\\ \\`\\`\\\\/'/";
    logo[3] = "    \\ \\  __ \\ \\ , ` \\ \\ \\L_L\\ \\ ,  /`\\ `\\ /'   ";
    logo[4] = "     \\ \\ \\/\\ \\ \\ \\`\\ \\ \\ \\/, \\ \\ \\\ \\  `\\ \\ \\  ";
    logo[5] = "      \\ \\_\\ \\_\\ \\_\\ \\_\\ \\____/\\ \\_\\ \\_\\ \\ \\_\\  ";
    logo[6] = "       \\/_/\\/_/\\/_/\\/_/\\/___/  \\/_/\\/_/  \\/_/ ";
    logo[7] = "         ____    ______   ____    ____    ____      ";
    logo[8] = "        /\\  _`\\ /\\__  _\\ /\\  _`\\ /\\  _`\\ /\\  _`\\   ";
    logo[9] = "        \\ \\ \\L\\ \\/_\/\\ \\/ \\ \\ \\L\\ \\ \\ \\/\\ \\ \\,\\L\\_\\  ";
    logo[10] = "         \\ \\  _ <' \\ \\ \\  \\ \\ ,  /\\ \\ \\ \\ \\/_\\__ \\  ";
    logo[11] = "          \\ \\ \\L\\ \\ \\_\\ \\__\\ \\ \\\\ \\\\ \\ \\_\\ \\/\\ \\L\\ \\ ";
    logo[12] = "           \\ \\____/ /\\_____\\\\ \\_\\ \\_\\ \\____/\\ `\\____\\ ";
    logo[13] = "            \\/___/  \\/_____/ \\/_/\\/ /\\/___/  \\/_____/ ";
}

void Game::initSun()
{
    sun[0] = "###########";
    sun[1] = "##########";
    sun[2] = "#########";
    sun[3] = "######";
    sun[4] = "###";
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

    top = newwin(toprow, col, 0, 0);
    btm = newwin(btmrow, col, btmcol, 0);

    refresh();

    //Opprette noen fargepar
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);

}

void Game::welcomeScr()
{
    wattroff(top, A_BOLD);
    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);

    wattron(top, A_BOLD | COLOR_PAIR(4));
    //Printe ut sola
    for(int i = 0; i < sun.size(); i++)
        mvwaddstr(top,i+1,1, sun[i].c_str());
    wattroff(top, COLOR_PAIR(4));

    wattron(top, A_BOLD | COLOR_PAIR(1));
    //Printe ut logoen
    for(int i = 0; i < logo.size(); i++)
        mvwaddstr(top,i+7,10, logo[i].c_str());
    wattroff(top, COLOR_PAIR(1));


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
        if(in == 49) //Nytt spill
        {
            wclear(btm);
            box(btm, 0, 0);
            mvwaddstr(btm,0,1, "Select stage:");
            mvwaddstr(btm,1,1, "1 - The Earth");
            mvwaddstr(btm,2,1, "2 - The Moon");
            mvwaddstr(btm,3,1, "3 - Jupiter");
            mvwaddstr(btm,4,1, "4 - Abort");
            wrefresh(btm);

            while(true)
            {
                stagePick = getch();
//                int in2 = getch();
                if(stagePick == 49)
                {
                    startStage(1);
                    welcomeScr();
                    break;
                }
                else if(stagePick == 50)
                {
                    startStage(2);
                    welcomeScr();
                    break;
                }
                else if(stagePick == 51)
                {
                    startStage(2);
                    welcomeScr();
                    break;
                }
                else if(stagePick == 52)
                {
                    welcomeScr();
                    break;
                }
            }
        }
        else if(in == 50) //Settings
        {
            // Settings?

        }
        else if(in == 51) //Hjelp
        {
            wclear(top);
            box(top, 0, 0);
            mvwaddstr(btm,1,1, "Her det kommer det litt hjelp");
            mvwaddstr(btm,2,1, "Dette er andre linje");
            mvwaddstr(btm,3,1, "Og tredje...");
            mvwaddstr(btm,4,1, "Til slutt den siste!");
            wrefresh(top);
            getch();
            welcomeScr();
            break;
        }
        else if(in == 52) //Avslutt
        {
            exit = true;
            break;
        }
    }
    if(!exit) userInput();

}

void Game::startStage(int in)
{
    Stage *stage = new Stage(in);
    vector<string> bird = stage->getBird();
    int speed = 10;
    int angle = 30;
    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);
    wrefresh(top);
    wrefresh(btm);

    for(int i = 0; i < bird.size(); i++)
    {
        mvwaddstr(top, 27+i, 1, bird[i].c_str());
        mvwaddstr(top, 30, stage->getEnemyDistance()-5, "[");
        mvwaddstr(top, 30, stage->getEnemyDistance(), "X");
        mvwaddstr(top, 30, stage->getEnemyDistance()+5, "]");
    }

    mvwprintw(btm, 1, 1, "Speed: %d", speed);
    mvwprintw(btm, 2, 1, "Angle: %d", angle);
    wrefresh(top);
    wrefresh(btm);

    while(true)
    {
        int in = getch();
        if(in == KEY_UP)
        {
            speed++;
            mvwprintw(btm, 1, 1, "Speed: %d", speed);
            wrefresh(btm);
        }
        else if(in == KEY_DOWN)
        {
            speed--;
            mvwprintw(btm, 1, 1, "Speed: %d", speed);
            wrefresh(btm);
        }
        else if(in == KEY_LEFT)
        {
            angle++;
            mvwprintw(btm, 2, 1, "Angle: %d", angle);
            wrefresh(btm);
        }
        else if(in == KEY_RIGHT)
        {
            angle--;
            mvwprintw(btm, 2, 1, "Angle: %d", angle);
            wrefresh(btm);
        }
        else if(in == 97) //bokstaven a
        {
            stage->setUserInput((float) speed, (float) angle, 1);
            wrefresh(top);
            for(int i = 0; i < (int) stage->getVector_Y().size(); i++)
            {
                wclear(top);
                for(int j = 0; j < bird.size(); j++){
                        mvwaddstr(top, 27+stage->getVector_Y().at(i)+j, i+2, bird[j].c_str());
                        mvwaddstr(top, 30, stage->getEnemyDistance()-5, "[");
                        mvwaddstr(top, 30, stage->getEnemyDistance(), "X");
                        mvwaddstr(top, 30, stage->getEnemyDistance()+5, "]");
                }
                wrefresh(top);
                usleep(100000);
                //if( i!= stage->getVector_Y().size()-1) wclear(top);
            }
//                if(!stage->gameCheck()){
////                    mvwaddstr(top, 30+5, 3+2, "BKAAA");
////                    wrefresh(top);
//                }
            if(!stage->gameOver()){
                wclear(top);
                mvwaddstr(top, 30, stage->getEnemyDistance()-5, "[");
                mvwaddstr(top, 30, stage->getEnemyDistance()-7, "BKAAAAA...dead");
                mvwaddstr(top, 30, stage->getEnemyDistance()+5, "]");
                wrefresh(top);
                finish();
                sleep(20);
            }
            else if(stage->gameOver()){
                wclear(top);
                mvwaddstr(top, 30, stage->getEnemyDistance()-5, "[");
                mvwaddstr(top, 30, stage->getEnemyDistance()-2, "-50HP");
                mvwaddstr(top, 30, stage->getEnemyDistance()+5, "]");
                wrefresh(top);
                sleep(20);
//                delete stage;
                startStage(stagePick);
            }
            else
                break;
//                else
//                    break;

//            do{
//                stage->setUserInput((float) speed, (float) angle, 1);
//                for(int i = 0; i < stage->getVector_Y().size(); i++)
//                {
//                        mvwprintw(top, stage->getVector_Y().at(i)+30, i+2, "Angle: %d", angle);
//                        wrefresh(top);
//                        usleep(100000);
//                        if( i!= stage->getVector_Y().size()-1) wclear(top);
//                }
//            }while(!stage->gameCheck());

        }
        else if(in == KEY_F(1))
        {
            break;
        }
    }
    delete stage;
    welcomeScr();
    wrefresh(top);
    wrefresh(btm);
    userInput();
}

void Game::finish(){
    wclear(btm);
    box(btm, 0, 0);
    //Printe ut menyen
    mvwaddstr(btm,0,1, "Meny");
    mvwaddstr(btm,1,1, "1. Start nytt spill");
    mvwaddstr(btm,2,1, "2. Highscore");
    mvwaddstr(btm,4,1, "4. Avslutt");
    wrefresh(btm);
}

Game::Game()
{
    initScreen();
    initSun();
    initLogo();
    attron(COLOR_PAIR(6));

    box(top, 0, 0);
    box(btm, 0, 0);

    welcomeScr();
    wrefresh(top);
    wrefresh(btm);

    userInput();

    delwin(top);
    delwin(btm);

    endwin();
}

Game::~Game()
{
    //dtor
}
