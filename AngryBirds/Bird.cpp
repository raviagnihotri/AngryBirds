#include "Bird.h"

Bird::Bird(int w)
{
    weight = w;
}

void Bird::setSpeed(int s){
    speed = s;
}

int Bird::getSpeed(){
    return speed;
}

int Bird::getWeight(){
    return weight;
}

Bird::~Bird()
{
    //dtor
}
