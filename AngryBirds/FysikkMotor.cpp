#include "FysikkMotor.h"
#include <iostream>
#include <cmath>
#define PI 3.14159265

using namespace std;

float sinSpeed;
float cosSpeed;
float timeY;
float timeYHeight;
float distanceYHeight;
float totalHeight;
float timeYDown;
float totalTime;
float totalDistance;
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
        distanceYHeight = (sinSpeed * timeYHeight) - (0.5*9.81 * (timeYHeight * timeYHeight));
        totalHeight = height + distanceYHeight;
        totalHeightHelper = lengdeHelper--;
        timeYDown = sqrt(totalHeight / (0.5 * 9.81));
        totalTime = timeYDown + timeYHeight;
        totalDistance = cosSpeed * totalTime;

        cout << "X: " << i << "Y: " << totalHeightHelper << endl;
    }
        cout << "Total distanse: " << ceil(totalDistance) << " meter" << endl;

//    return ceil(totalDistance);
}

FysikkMotor::~FysikkMotor()
{
    //dtor
}
