#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::updateEnemyHP(){
    hp = hp - 50;
}

void Enemy::resetHP(){
    hp = 100;
}

int Enemy::getEnemyHP(){
    return hp;
}

Enemy::~Enemy()
{
    //dtor
}
