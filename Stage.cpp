#include "Stage.h"
#include "Bird.h"
#include "Enemy.h"
#include <iostream>
#include <cmath>

using namespace std;

    Bird *birdObject;
    Enemy *enemyObject = new Enemy();

Stage::Stage(int st, int ed)
{
    stage = st;
    enemyDistance = ed;
    setupStage();
    birdObject = new Bird();
    headShot = false;
}

//Velger tyngdekraft
void Stage::setupStage(){
    if(stage == 1){
        gravity = 9.81;
    }
    else if(stage == 2){
        gravity = 20.15;
    }
    else if(stage == 3){
        gravity = 2.0;
    }
}

//setter fart, vinkel og høyde(ikke implementert funksjon)
void Stage::setUserInput(float s, float a, float h){
    speed = s;
    angle = a;
    height = h;
    engine();
}

//Håndterer når man treffer eller bommer på enemy
bool Stage::enemyHit(){
    int ceil_distanceX = ceil(distance_X);
    if(ceil_distanceX == getEnemyDistance()){
        headShot = true;
        if(enemyObject->getHP() != 0){
            enemyObject->headShot();
        }
        return true;
    }
    if(ceil_distanceX < getEnemyDistance() && ceil_distanceX > getEnemyDistance()-5){
        if(enemyObject->getHP() != 0)
            enemyObject->sideShot();
        return true;
    }
    else if(ceil_distanceX > getEnemyDistance() && ceil_distanceX < getEnemyDistance()+5){
        if(enemyObject->getHP() != 0)
            enemyObject->sideShot();
        return true;
    }

    return false;
}

//Om enemy er ødelagt eller ikke
bool Stage::gameOver(){
        return enemyObject->getHP() <= 0? true : false;
}

//Distansen til enemy som er satt statisk
int Stage::getEnemyDistance(){
    return enemyDistance;
}

//Resetter enemy HP til 100
void Stage::resetEnemyHP(){
    enemyObject->resetHP();
}

int Stage::getEnemyHP(){
    enemyObject->getHP();
}

bool Stage::getHeadshot(){
    return headShot;
}

//Fysikkmotoren så vi kan se og beregne banen til fuglen med en gitt vinkel og fart
void Stage::engine(){

    angle = angle * (2 * 3.14 / 360);

    speed_Y = sin(angle)*speed;
    totalTime = (-speed_Y - sqrt((speed_Y*speed_Y) - (4*(-gravity*0.5)*1))) / (2*-gravity*0.5);
    distance_Y = (speed_Y*totalTime) + (0.5*-gravity*(totalTime*totalTime));

    speed_X = cos(angle)* speed;
    distance_X = speed_X * totalTime;

    for(coord_X = 0; coord_X <= distance_X; coord_X++){
        time_X = coord_X / (speed * cos(angle));
        coord_Y = (-0.5 * gravity * (time_X * time_X) + speed * sin(angle) * time_X) * -1;

        if(coord_Y <= 0){
            vectorY.push_back(coord_Y);
        }
    }

//    cout << "Speed_y: " << speed_Y << endl;
//    cout << "Distance_y: " << distance_Y << endl;
//    cout << "Speed_x: " << speed_X << endl;
//    cout << "Distance_x: " << distance_X << endl;
//    cout << "Totaltime: " << totalTime << endl;
}

//Henter ut distansen til X koordinatet
int Stage::getDistance_X(){
    return ceil(distance_X);
}

vector<string> Stage::getBird()
{
    vector<string> bird(5);
    bird[0] = "   /^``^\\";
    bird[1] = " \\/   \\_/\\";
    bird[2] = "--1 .--00|";
    bird[3] = " /1    ->|";
    bird[4] = "   \\_____/";
    return bird;
}

vector<string> Stage::getEnemy()
{
    vector<string> enemy(5);
    enemy[0] = "  |||||||  ";
    enemy[1] = " /__   __\\";
    enemy[2] = "<| ¤\\ /¤ |>";
    enemy[3] = " |   U   |";
    enemy[4] = "  \\_`--'_/ ";

    return enemy;
}

vector<float> Stage::getVector_Y()
{
    return vectorY;
}

Stage::~Stage()
{
    //dtor
}
