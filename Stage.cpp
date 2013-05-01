#include "Stage.h"
#include "Bird.h"
#include "Enemy.h"
#include <iostream>
#include <cmath>

using namespace std;

Stage::Stage(int st)
{
    stage = st;
    setupStage();
}

void Stage::setupStage(){
    if(stage == 1){
        gravity = 9.81;
    }
    else if(stage == 2){
        gravity = 8.15;
    }
    else if(stage == 3){
        gravity = 14.0;
    }
}

void Stage::setUserInput(float s, float a, float h){
    speed = s;
    angle = a;
    height = h;

    engine();
}

bool Stage::gameCheck(){
//    if(== distance_X){
//        destroyed = true;
//    }
    return destroyed;
}

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

vector<string> Stage::getBird()
{
    vector<string> bird(5);
    bird[0] = "     /^``^\\";
    bird[1] = "   \\/   \\_/\\";
    bird[2] = "  --1 .  00|";
    bird[3] = "   /1    ->|";
    bird[4] = "     \\_____/";
    return bird;
}

Stage::~Stage()
{
    //dtor
}
