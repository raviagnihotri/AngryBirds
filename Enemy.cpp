#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::headShot(){
    hp = 0;
}

void Enemy::sideShot(){
    hp = hp - 50;
}

void Enemy::resetHP(){
    hp = 100;
}

int Enemy::getHP(){
    return hp;
}

Enemy::~Enemy()
{
    //dtor
}
