#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
    public:
        Enemy(); //antTargets
        void headShot();//Dersom fuglen går eksakt 140m
        void sideShot();//Dersom fuglen treffer mellom 135m og 145m
        int getHP();//Henter ut HP til enemy
        void resetHP();//Resetter HP til enemy
        virtual ~Enemy();
    protected:
    private:
        int antEnemies;
        int hp = 100;
};

#endif // TARGET_H
