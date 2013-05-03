#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
    public:
        Enemy(); //antTargets
        void headShot();
        void sideShot();
        int getHP();
        void resetHP();
        virtual ~Enemy();
    protected:
    private:
        int antEnemies;
        int hp = 100;
};

#endif // TARGET_H
