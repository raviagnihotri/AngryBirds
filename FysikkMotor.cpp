#include "FysikkMotor.h"
#include <iostream>
#include <cmath>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sstream>

using namespace std;

FysikkMotor::FysikkMotor(float s, float a, float h)
{
//    cout << "Skriv inn speed: " << ends;
//    cin >> speed;
//    cout << "Skriv inn grad: " << ends;
//    cin >> angle;
//    cout << "Skriv inn høyde: " << ends;
//    cin >> height;
    speed = s;
    angle = a;
    height = h;
    engine();
}

float FysikkMotor::getSpeed(){
    return speed;
}

float FysikkMotor::getAngle(){
    return angle;
}

float FysikkMotor::getHeight(){
    return height;
}

void FysikkMotor::engine(){

    angle = angle * (2 * 3.14 / 360);

    time_Y = ((speed*speed) * sin(2*angle)) / 9.81;

    for(coord_X = 0; coord_X <= time_Y; coord_X++){
        time_X = coord_X / (speed * cos(angle));
        coord_Y = -0.5 * 9.81 * (time_X * time_X) + speed * sin(angle) * time_X;

        if(coord_Y > 0){
//            cout << "(" << coord_X << ", " << coord_Y << ")" << endl;
            mvwaddstr(top,coord_Y,coord_X,"..Mjau");
            wrefresh(top);
            sleep(1);
        }
    }

//    lengdeHelper = height;

//http://www.youtube.com/watch?v=-W3RkgvLrGI&list=PLjB6rBMzV0MY-tamn7GAEWAW7nyjUl3KS

//    for(int i = 0; i <= LENGDE; i++){
//        sinSpeed = sin(getAngle()*PI/180) * getSpeed();
//        cosSpeed = cos(getAngle()*PI/180) * getSpeed();
//        timeY = (sinSpeed / (0.5*9.81));
//        timeYHeight = timeY / 2;
//        distanceY_up = (sinSpeed * timeYHeight) - (0.5*9.81 * (timeYHeight * timeYHeight));
//        totalHeight = height + distanceY_up;
//        totalHeightHelper = lengdeHelper--;
//        timeYDown = sqrt(totalHeight / (0.5 * 9.81));
//        totalTime = timeYDown + timeYHeight;
//        distanceX = cosSpeed * totalTime;
//    }

//    int ceil_distanceX_Coord = ceil(distanceX_Coord);
//    int distanceX_Coord;
//    int distanceY_Coord = 0;
//    int ceil_cosSpeed = ceil(cosSpeed);
//    int ceil_sinSpeed = ceil(sinSpeed);
//    int ceil_totalTime = ceil(totalTime);
//    int ceil_distanceX = ceil(distanceX);
//    int ceil_distanceY = ceil(totalHeight);

//    for(int i = 0; i < ceil_totalTime; i++){
//        distanceX_Coord = ceil_cosSpeed * i;
//        distanceY_Coord = tan(angle) * i;
//        cout << "(" << distanceX_Coord << ", " << distanceY_Coord << ")" << endl;
//    }

//    for(int i = 0; i < ceil_distanceX; i++){
//        distanceY_Coord = -tan(angle) * i;
//        cout << "(" << i << ", " << distanceY_Coord << ")" << endl;
//    }
//    for(int i = 0; i <= ceil_distanceX; i++){
//        cout << "X: " << i << endl;
//    }

//    for(int i = 0; i <= ceil_distanceY; i++){
//        cout << "Y: " << i << endl;
//    }
//        cout << "Distance Y, up: " << ceil(distanceY_up) << " meter" << endl;
//        cout << "Time Y, up " << ceil(timeYHeight) << " sec" << endl;
//        cout << "Distance Y, down: " << ceil(totalHeight) << " meter" << endl;
//        cout << "Time total, down: " << ceil(timeYDown) << " sec" << endl;
//        cout << "Distance X: " << ceil(distanceX) << " meter" << endl;
//        cout << "Time total: " << ceil(totalTime) << " sec" << endl;

//    return ceil(totalDistance);
}

FysikkMotor::~FysikkMotor()
{
    //dtor
}
