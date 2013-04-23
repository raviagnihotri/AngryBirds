#include "Game.h"
#include "Stage.h"
#include <iostream>

using namespace std;

int bird;
int target;
float gravity;

Game::Game()
{
    welcomeScr();
}


void Game::welcomeScr(){
    cout << "Welcome to remake of Angry Birds!" << endl;
    cout << "Pick number of birds: " << ends;
    cin >> bird;
    cout << "Pick number of targets: " << ends;
    cin >> target;
    cout << "Pick gravity(i.e: 8.9): " << ends;
    cin >> gravity;
    Stage stageObject(bird,target,gravity);


}

Game::~Game()
{
    //dtor
}
