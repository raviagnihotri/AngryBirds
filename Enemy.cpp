#include "Enemy.h"

Enemy::Enemy()
{
}

//Dersom fuglen går eksakt 140m
void Enemy::headShot(){
    hp = 0;
}

//Dersom fuglen treffer mellom 135m og 145m
void Enemy::sideShot(){
    hp = hp - 50;
}

//Resetter HP til enemy
void Enemy::resetHP(){
    hp = 100;
}

//Henter ut HP til enemy
int Enemy::getHP(){
    return hp;
}

Enemy::~Enemy()
{
    //dtor
}
