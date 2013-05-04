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
vector<string> hs(5);
vector<string> ns(5);
vector<string> go(5);
vector<string> text(11);

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

void Game::headShot()
{
    hs[0] = " _   _ _____    _    ____    ____  _   _  ___ _____ ";
    hs[1] = "| | | | ____|  / \\  |  _ \\  / ___|| | | |/ _ \\_   _|";
    hs[2] = "| |_| |  _|   / _ \\ | | | | \\___ \\| |_| | | | || |  ";
    hs[3] = "|  _  | |___ / ___ \\| |_| |  ___) |  _  | |_| || | ";
    hs[4] = "|_| |_|_____/_/   \\_\\____/  |____/|_| |_|\\___/ |_| ";
//    hs[0] = "              ____                                                                           ______                 ";
//    hs[1] = " |         | |                  .'.       |``````.                     ..'''' |         |  .~      ~.  `````|`````  ";
//    hs[2] = " |_________| |______          .''```.     |       |                 .''       |_________| |          |      |       ";
//    hs[3] = " |         | |              .'       `.   |       |              ..'          |         | |          |      |       ";
//    hs[4] = " |         | |___________ .'           `. |......'         ....''             |         |  `.______.'       |       ";
}

void Game::noobShot()
{
    ns[0] = " _   _  ___   ___  ____    ____  _   _  ___ _____ ";
    ns[1] = "| \\ | |/ _ \\ / _ \\| __ )  / ___|| | | |/ _ \\_   _|";
    ns[2] = "|  \\| | | | | | | |  _ \\  \\___ \\| |_| | | | || |  ";
    ns[3] = "| |\\  | |_| | |_| | |_) |  ___) |  _  | |_| || | ";
    ns[4] = "|_| \\_|\\___/ \\___/|____/  |____/|_| |_|\\___/ |_| ";
//    ns[0] = "                   ______       ______     ____                                               ______                 ";
//    ns[1] = " |..          |  .~      ~.   .~      ~.  |    ~.                       ..'''' |         |  .~      ~.  `````|`````  ";
//    ns[2] = " |  ``..      | |          | |          | |____.'_                   .''       |_________| |          |      |       ";
//    ns[3] = " |      ``..  | |          | |          | |       ~.              ..'          |         | |          |      |       ";
//    ns[4] = " |          ``|  `.______.'   `.______.'  |_______.'        ....''             |         |  `.______.'       |  ";
}

void Game::gameOver(){
    go[0] = "  ____    _    __  __ _____    _____     _______ ____ ";
    go[1] = " / ___|  / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\ ";
    go[2] = "| |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) |";
    go[3] = "| |_| |/ ___ \\| |  | | |___  | |_| |\\ \V / | |___|  _ < ";
    go[4] = " \\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_\\";
}

void Game::helpText()
{
    text[0] = "Velkommen til Angry Nerds - spillet som er en skamfull rip-off av det mindre kjente spillet Angry...Birds.";
    text[1] = "==========================================================================================================";
    text[2] = "1. Du velger først et brett/en planet";
    text[3] = "2. Deretter bruker du piltastene til å sette ønsket fart og vinkel på fuglen";
    text[4] = "3. Trykk 'A' for å slippe løs fuglen";
    text[5] = "4. Se fuglens praktfulle ferd mot den stygge nerden";
    text[6] = "5. Om du treffer rett i knollen på nerden, dreper du han umiddelbart";
    text[7] = "   Treffer du ved siden av mister nerden 50 Health Points";
    text[8] = "   Bommer du...da har du bommet";
    text[9] = "";
    text[10] = "--Trykk en tast for å se den fine fuglen fly--";
}

int Game::randomNumber(int s)
{
    return (rand()%s);
}

void Game::printScenery()
{
    box(top, 0, 0);
    box(btm, 0, 0);
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
    headShot();
    noobShot();
    gameOver();
    helpText();
    wattroff(top, A_BOLD);
    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);

    int tmpspeed = 0;
    int tmpangle = 0;

    int key;
    nodelay(stdscr, TRUE);
    mvwaddstr(btm,1,1, "Trykk en tast for å begynne! (om du har gjort det, må du vente til fuglen har landet");
    wrefresh(btm);

    while(true)
    {
        tmpspeed = randomNumber(35);
        tmpangle = randomNumber(70);

        Stage *stage = new Stage(randomNumber(2)+1);
        vector<string> bird = stage->getBird();

        if(key = getch() == ERR)
        {
            stage->setUserInput((float) tmpspeed, (float) tmpangle, 1); //regner ut bane/trajectory
            int atgrass = ((topy-2)-bird.size()); //bakkenivå
            for(int i = 0; i < (int) stage->getVector_Y().size(); i++)
            {
                wclear(top);

                wattron(top, A_BOLD | COLOR_PAIR(1));
                //Printe ut logoen i midten
                for(int i = 0; i < logo.size(); i++)
                    mvwaddstr(top,i+9,(topx-200)/2, logo[i].c_str());
//                    mvwaddstr(top,i+9,(topx-55)/2, logo[i].c_str());
                wattroff(top, COLOR_PAIR(1));

                for(int j = 0; j < bird.size(); j++)
                    mvwaddstr(top, atgrass+stage->getVector_Y().at(i)+j, i+2, bird[j].c_str());
                printScenery();
                wrefresh(top);
                speed > 30 ? usleep(100000 * (1+((speed-30))/100)) : usleep(100000);
            }
            delete stage;
        }
        else
        {
            delete stage;
            break;
        }
    }

    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);

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
    antMiss = 3;
    bool exit = false;

    while(true)
    {
        int in = getch();
        if(in == 49) //Nytt spill
        {
            wclear(btm);
            box(btm, 0, 0);
            mvwaddstr(btm,0,1, "Select stage:");
            mvwaddstr(btm,1,1, "1 - The Earth  (Regular gravity)");
            mvwaddstr(btm,2,1, "2 - The Moon  (Low gravity)");
            mvwaddstr(btm,3,1, "3 - Jupiter  (High gravity)");
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
            printScenery();
            box(top, 0, 0);

            wattron(top, A_BOLD | COLOR_PAIR(1));
            for(int i=0; i < text.size(); i++)
                mvwaddstr(top, i+10, 25, text[i].c_str());
            wrefresh(top);
            nodelay(stdscr, FALSE);
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
    vector<string> enemy = stage->getEnemy();
    atgrass = ((topy-2)-bird.size()); //bakkenivå
    speed = 10;
    angle = 30;
    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);
    wrefresh(top);
    wrefresh(btm);

    //Printer ut fuglen og enemy før launch
    for(int i = 0; i < bird.size(); i++)
    {
        mvwaddstr(top, atgrass+i, 1, bird[i].c_str());
        mvwaddstr(top, atgrass+i, stage->getEnemyDistance()-6, enemy[i].c_str());
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
        else if(in == 97){ //Liftoff!
            wclear(top);
            printScenery();
            stage->setUserInput((float)speed, (float)angle, 1);
            for(int i = 0; i < (int)stage->getVector_Y().size(); i++)
            {
                wclear(top);
                printScenery();
                for(int k = 0; k < bird.size(); k++)
                {
                    mvwaddstr(top, atgrass+stage->getVector_Y().at(i)+k, i+2, bird[k].c_str());
                    mvwaddstr(top, atgrass+k, stage->getEnemyDistance()-6, enemy[k].c_str());
                }
                wrefresh(top);
                speed > 30 ? usleep(100000 * (1+((speed-30))/100)) : usleep(100000);
                //if( i!= stage->getVector_Y().size()-1) wclear(top);
            }

            if(stage->enemyHit()){
                if(stage->gameOver()){
                    wclear(top);
                    printScenery();
                    if(stage->getHeadshot()){
                        //print ut headshotlogo
                        for(int j = 0; j < hs.size(); j++)
                            mvwaddstr(top,j+9,(topx-55)/2, hs[j].c_str());
                    }
                    else{
                        //print ut DEADlogo
                        for(int j = 0; j < enemy.size(); j++)
                        {
                            if(j == 3) enemy[3] = "<| -DEAD |>";
                            mvwaddstr(top, atgrass+j, stage->getEnemyDistance()-6, enemy[j].c_str());
                        }
                    }
                    wrefresh(top);
                    stage->resetEnemyHP();
                    delete stage;
                    finish();
                }
                else{
                    wclear(top);
                    printScenery();
                    //print ut noobshot logo
                    for(int j = 0; j < enemy.size(); j++)
                    {
                        if(j == 3) enemy[3] = "<| -50HP |>";
                        mvwaddstr(top, atgrass+j, stage->getEnemyDistance()-6, enemy[j].c_str());
                    }
                    wrefresh(top);
                    sleep(1);
                    delete stage;
                    startStage(stagePick);
                }
            }
            else if(!stage->enemyHit()){
                antMiss--;
                if(antMiss != 0){
                    wclear(top);
                    printScenery();
                    for(int j = 0; j < ns.size(); j++)
                        mvwaddstr(top,j+9,(topx-55)/2, ns[j].c_str());
                    for(int j = 0; j < enemy.size(); j++)
                    {
                        if(j == 3) enemy[3] = "<| -MISS |>";
                        mvwaddstr(top, atgrass+j, stage->getEnemyDistance()-6, enemy[j].c_str());
                    }
                    wrefresh(top);
                    sleep(1);
                    delete stage;
                    startStage(stagePick);
                }
                else if(antMiss == 0){
                    //GAME OVER logo
                    wclear(top);
                    printScenery();
                    for(int j = 0; j < go.size(); j++)
                        mvwaddstr(top,j+9,(topx-55)/2, go[j].c_str());
                    for(int j = 0; j < enemy.size(); j++)
                    {
                        if(j == 3) enemy[3] = "<| -MISS |>";
                        mvwaddstr(top, atgrass+j, stage->getEnemyDistance()-6, enemy[j].c_str());
                    }
                    wrefresh(top);
                    stage->resetEnemyHP();
                    delete stage;
                    finish();
                }
            }
        }
    }
    delete stage;
}

void Game::finish(){
    wclear(btm);
    box(btm, 0, 0);
    //Printe ut menyen
    mvwaddstr(btm,0,1, "Meny");
    mvwaddstr(btm,1,1, "1. Start spill");
    mvwaddstr(btm,2,1, "2. Endre på noe");
    mvwaddstr(btm,3,1, "3. Hjelp");
    mvwaddstr(btm,4,1, "4. Avslutt");
    wrefresh(btm);
    userInput();
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
