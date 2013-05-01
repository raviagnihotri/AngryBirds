#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::updateEnemyHP(){
    hp = hp - 50;
}

int Enemy::getEnemyHP(){
    return hp;
}

Enemy::~Enemy()
{
    //dtor
}
