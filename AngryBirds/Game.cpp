#include "Game.h"
#include "Stage.h"
#include <iostream>

using namespace std;

Game::Game()
{
    welcomeScr();
}


void Game::welcomeScr(){
    cout << "Welcome to remake of Angry Birds!" << endl;
    cout << "Velg brett: " << endl;

    Stage stageObject;
}

Game::~Game()
{
    //dtor
}
