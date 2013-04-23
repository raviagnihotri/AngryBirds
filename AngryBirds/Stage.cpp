#include "Stage.h"
#include "Bird.h"
#include "Target.h"
#include <iostream>

using namespace std;

Stage::Stage(int b, int t, float g)
{
    birds = b;
    targets = t;
    gravity = g;

    settingsGame();
}

int Stage::getBirds(){
    return birds;
}

int Stage::getTargets(){
    return targets;
}
float Stage::getGravity(){
    return gravity;
}
void Stage::settingsGame(){
    cout << "Time to set some settings on your bird to fly: " << endl;
    cout << "Set speed: " << ends;
    cin >> speed;

    cout << "Set angle: " << ends;
    cin >> angle;
}

Stage::~Stage()
{
    //dtor
}
