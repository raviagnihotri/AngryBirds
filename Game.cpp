#include <iostream>
#include "Game.h"
#include "Stage.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sstream>
#include <cstdlib>

using namespace std;

int bird;
int target;
float gravity;

WINDOW * top;
WINDOW * btm;
int toprow, topx, topy;

vector<string> logo(14);
vector<string> sun(7);

void Game::initLogo()
{
    logo[0] =  "    ______  __  __  ____    ____    __   __   ";
    logo[1] = "   /\\  _  \\/\\ \\/\\ \\/\\  _`\\ /\\  _`\\ /\\ \\ /\\ \\ ";
    logo[2] = "   \\ \\ \\L\\ \\ \\ `\\\\ \\ \\ \\L\\_\\ \\ \\L\\ \\`\\`\\\\/'/";
    logo[3] = "    \\ \\  __ \\ \\ , ` \\ \\ \\L_L\\ \\ ,  /`\\ `\\ /'   ";
    logo[4] = "     \\ \\ \\/\\ \\ \\ \\`\\ \\ \\ \\/, \\ \\ \\\ \\  `\\ \\ \\  ";
    logo[5] = "      \\ \\_\\ \\_\\ \\_\\ \\_\\ \\____/\\ \\_\\ \\_\\ \\ \\_\\  ";
    logo[6] = "       \\/_/\\/_/\\/_/\\/_/\\/___/  \\/_/\\/_/  \\/_/ ";
    logo[7] = "          __  __  ____    ____    ____    ____         ";
    logo[8] = "         /\\ \\/\\ \\/\\  _`\\ /\\  _`\\ /\\  _`\\ /\\  _`\\       ";
    logo[9] = "         \\ \\ `\\\\ \\ \\ \\L\\_\\ \\ \\L\\ \\ \\ \\/\\ \\ \\,\\L\\_\\     ";
    logo[10] = "          \\ \\ , ` \\ \\  _\\L\\ \\ ,  /\\ \\ \\ \\ \\/_\\__ \\     ";
    logo[11] = "           \\ \\ \\`\\ \\ \\ \\L\\ \\ \\ \\\\ \\\\ \\ \\_\\ \\/\\ \\L\\ \\   ";
    logo[12] = "            \\ \\_\\ \\_\\ \\____/\\ \\_\\ \\_\\ \\____/\\ `\\____\\  ";
    logo[13] = "             \\/_/\\/_/\\/___/  \\/_/\\/ /\\/___/  \\/_____/  ";
}

void Game::initSun()
{
    sun[0] = "############################";
    sun[1] = "#########################";
    sun[2] = "##################";
    sun[3] = "##############";
    sun[4] = "#########";
    sun[5] = "####";
    sun[6] = "#";
}

int Game::randomNumber(int s)
{
    return (rand()%s);
}

void Game::printScenery()
{
    wattron(top, A_BOLD | COLOR_PAIR(4));
    //Printe ut sola...
    for(int i = 0; i < sun.size(); i++)
        mvwaddstr(top,i+1,1, sun[i].c_str());
    wattroff(top, A_BOLD | COLOR_PAIR(4));

    wattron(top, COLOR_PAIR(7));
    //...og litt gress og blomster
    for(int i = 1; i < topx-1; i++)
        mvwaddstr(top,topy-2,i, "|");

    for(int i = 1; i < 15; i++)
    {
        wattron(top, A_BOLD | COLOR_PAIR(8+(i%3)));
        mvwaddstr(top,topy-3,randomNumber(topx-1), "*");
    }


    wattroff(top, COLOR_PAIR(4));
}

void Game::initScreen()
{
    // Start ncurses
    initscr();

    int row, col, topcol, btmrow, btmcol;

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

    topy = getmaxy(top);
    topx = getmaxx(top);

    refresh();

    //Opprette noen fargepar
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_GREEN);
    init_pair(9, COLOR_BLUE, COLOR_GREEN);
    init_pair(10, COLOR_YELLOW, COLOR_GREEN);

}

void Game::welcomeScr()
{
    wattroff(top, A_BOLD);
    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);

    int tmpspeed = 0;
    int tmpangle = 0;

    do
    {
        mvwaddstr(btm,1,1, "Trykk en tast for å begynne!");
        while( tmpspeed > 10 && tmpspeed < 90 && tmpangle > 5 && tmpangle < 85)
        {
            tmpspeed = randomNumber(90);
            tmpangle = randomNumber(85);
        }
        Stage *stage = new Stage(randomNumber(3));
        vector<string> bird = stage->getBird();

        stage->setUserInput((float) tmpspeed, (float) tmpangle, 1); //regner ut bane/trajectory
        int atgrass = ((topy-2)-bird.size()); //bakkenivå
        for(int i = 0; i < (int) stage->getVector_Y().size(); i++)
        {
            wclear(top);

            wattron(top, A_BOLD | COLOR_PAIR(1));
            //Printe ut logoen i midten
            for(int i = 0; i < logo.size(); i++)
                mvwaddstr(top,i+9,(topx-55)/2, logo[i].c_str());
            wattroff(top, COLOR_PAIR(1));

            for(int j = 0; j < bird.size(); j++)
                mvwaddstr(top, atgrass+stage->getVector_Y().at(i)+j, i+2, bird[j].c_str());
            printScenery();
            wrefresh(top);
            speed > 30 ? usleep(100000 * (1+((speed-30))/100)) : usleep(100000);
        }
        delete stage;

    } while(getch());

    wclear(top);

    wattron(top, A_BOLD | COLOR_PAIR(1));
    //Printe ut logoen i midten
    for(int i = 0; i < logo.size(); i++)
        mvwaddstr(top,i+9,(topx-55)/2, logo[i].c_str());
    wattroff(top, COLOR_PAIR(1));

    printScenery();

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
                int in2 = getch();
                if(in2 == 49)
                {
                    stagePick = 1;
                    startStage(1);
                    welcomeScr();
                    break;
                }
                else if(in2 == 50)
                {
                    stagePick = 2;
                    startStage(2);
                    welcomeScr();
                    break;
                }
                else if(in2 == 51)
                {
                    stagePick = 3;
                    startStage(2);
                    welcomeScr();
                    break;
                }
                else if(in2 == 52)
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
    do{
    speed = 10;
    angle = 30;
    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);
    wrefresh(top);
    wrefresh(btm);

    //Printer ut fuglen før launch
    for(int i = 0; i < bird.size(); i++)
    {
        mvwaddstr(top, ((topy-2)-bird.size())+i, 1, bird[i].c_str());
        mvwaddstr(top, 30, stage->getEnemyDistance()-5, "[");
        mvwaddstr(top, 30, stage->getEnemyDistance(), "X");
        mvwaddstr(top, 30, stage->getEnemyDistance()+5, "]");
    }
    printScenery();

    mvwprintw(btm, 1, 1, "Speed: %d", speed);
    mvwprintw(btm, 2, 1, "Angle: %d", angle);
    wrefresh(top);
    wrefresh(btm);

    while(true)
    {
        int in = getch();
        if(in == KEY_UP) //Juster fart opp
        {
            mvwprintw(btm, 1, 1, "                ");
            if(speed < 200) speed++;
            mvwprintw(btm, 1, 1, "Speed: %d", speed);
            wrefresh(btm);
        }
        else if(in == KEY_DOWN) //...ned
        {
            mvwprintw(btm, 1, 1, "                ");
            if(speed > 1) speed--;
            mvwprintw(btm, 1, 1, "Speed: %d", speed);
            wrefresh(btm);
        }
        else if(in == KEY_RIGHT) //Juster vinkel opp
        {
            mvwprintw(btm, 2, 1, "                ");
            if(angle < 90) angle++;
            mvwprintw(btm, 2, 1, "Angle: %d", angle);
            wrefresh(btm);
        }
        else if(in == KEY_LEFT) //...ned
        {
            mvwprintw(btm, 2, 1, "                ");
            if(angle > 1) angle--;
            mvwprintw(btm, 2, 1, "Angle: %d", angle);
            wrefresh(btm);
        }
        else if(in == 97) //Lift-off!
        {
            stage->setUserInput((float) speed, (float) angle, 1); //regner ut bane/trajectory
            wrefresh(top);
            int atgrass = ((topy-2)-bird.size()); //bakkenivå
            for(int i = 0; i < (int) stage->getVector_Y().size(); i++)
            {
                wclear(top);
                for(int j = 0; j < bird.size(); j++){
                        mvwaddstr(top, atgrass+stage->getVector_Y().at(i)+j, i+2, bird[j].c_str());
                        mvwaddstr(top, atgrass, stage->getEnemyDistance()-5, "[");
                        mvwaddstr(top, atgrass, stage->getEnemyDistance(), "X");
                        mvwaddstr(top, atgrass, stage->getEnemyDistance()+5, "]");
                }
                printScenery();
                wrefresh(top);
                speed > 30 ? usleep(100000 * (1+((speed-30))/100)) : usleep(100000);
                //if( i!= stage->getVector_Y().size()-1) wclear(top);
            }
                if(stage->enemyHit()){
                    if(stage->gameOver()){
                        wclear(top);
                        mvwaddstr(top, atgrass, stage->getEnemyDistance()-5, "[");
                        mvwaddstr(top, atgrass, stage->getDistance_X(), "dead");
                        mvwaddstr(top, atgrass, stage->getEnemyDistance()+5, "]");
                        wrefresh(top);
                        sleep(20);
                    }
                    else{
                        wclear(top);
                        mvwaddstr(top, atgrass, stage->getEnemyDistance()-5, "[");
                        mvwaddstr(top, atgrass, stage->getDistance_X(), "-50HP");
                        mvwaddstr(top, atgrass, stage->getEnemyDistance()+5, "]");
                        wrefresh(top);
//                        sleep(5);
    //                    startStage(stagePick);
                    }
                }
    //            if(!stage->gameOver()){
    //                wclear(top);
    //                mvwaddstr(top, 30, stage->getEnemyDistance()-5, "[");
    //                mvwaddstr(top, 30, stage->getEnemyDistance()-7, "BKAAAAA...dead");
    //                mvwaddstr(top, 30, stage->getEnemyDistance()+5, "]");
    //                wrefresh(top);
    //                finish();
    //                sleep(20);
    //            }
    //            else if(stage->gameOver()){
    //                wclear(top);
    //                mvwaddstr(top, 30, stage->getEnemyDistance()-5, "[");
    //                mvwaddstr(top, 30, stage->getEnemyDistance()-2, "-50HP");
    //                mvwaddstr(top, 30, stage->getEnemyDistance()+5, "]");
    //                wrefresh(top);
    //                sleep(20);
    ////                delete stage;
    //                startStage(stagePick);
    //            }
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
    }while(!stage->gameOver());
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
