#include "FysikkMotor.h"
#include <iostream>
#include <cmath>
#define PI 3.14159265

using namespace std;

float sinSpeed;
float cosSpeed;
float timeY;
float timeYHeight;
float distanceY_up;
float totalHeight;
float timeYDown;
float totalTime;
float distanceX;
float totalHeightHelper;
float lengdeHelper;

const int LENGDE = 20;

FysikkMotor::FysikkMotor()
{
    cout << "Skriv inn speed: " << ends;
    cin >> speed;
    cout << "Skriv inn grad: " << ends;
    cin >> angle;
    cout << "Skriv inn høyde: " << ends;
    cin >> height;

    totalDistanceX();
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

void FysikkMotor::totalDistanceX(){
    lengdeHelper = height;

//http://www.youtube.com/watch?v=-W3RkgvLrGI&list=PLjB6rBMzV0MY-tamn7GAEWAW7nyjUl3KS

    for(int i = 0; i <= LENGDE; i++){
        sinSpeed = sin(getAngle()*PI/180) * getSpeed();
        cosSpeed = cos(getAngle()*PI/180) * getSpeed();
        timeY = (sinSpeed / (0.5*9.81));
        timeYHeight = timeY / 2;
        distanceY_up = (sinSpeed * timeYHeight) - (0.5*9.81 * (timeYHeight * timeYHeight));
        totalHeight = height + distanceY_up;
        totalHeightHelper = lengdeHelper--;
        timeYDown = sqrt(totalHeight / (0.5 * 9.81));
        totalTime = timeYDown + timeYHeight;
        distanceX = cosSpeed * totalTime;
    }

//    int ceil_distanceX_Coord = ceil(distanceX_Coord);
    int distanceX_Coord;
    int distanceY_Coord = 0;
    int ceil_cosSpeed = ceil(cosSpeed);
    int ceil_sinSpeed = ceil(sinSpeed);
    int ceil_totalTime = ceil(totalTime);
    int ceil_distanceX = ceil(distanceX);
    int ceil_distanceY = ceil(totalHeight);

//    for(int i = 0; i < ceil_totalTime; i++){
//        distanceX_Coord = ceil_cosSpeed * i;
//        distanceY_Coord = tan(angle) * i;
//        cout << "(" << distanceX_Coord << ", " << distanceY_Coord << ")" << endl;
//    }

    for(int i = 0; i < ceil_distanceX; i++){
        distanceY_Coord = -tan(angle) * i;
        cout << "(" << i << ", " << distanceY_Coord << ")" << endl;
    }
//    for(int i = 0; i <= ceil_distanceX; i++){
//        cout << "X: " << i << endl;
//    }

//    for(int i = 0; i <= ceil_distanceY; i++){
//        cout << "Y: " << i << endl;
//    }
        cout << "Distance Y, up: " << ceil(distanceY_up) << " meter" << endl;
        cout << "Time Y, up " << ceil(timeYHeight) << " sec" << endl;
        cout << "Distance Y, down: " << ceil(totalHeight) << " meter" << endl;
        cout << "Time total, down: " << ceil(timeYDown) << " sec" << endl;
        cout << "Distance X: " << ceil(distanceX) << " meter" << endl;
        cout << "Time total: " << ceil(totalTime) << " sec" << endl;

//    return ceil(totalDistance);
}

FysikkMotor::~FysikkMotor()
{
    //dtor
}
