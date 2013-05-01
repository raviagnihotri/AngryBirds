#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
    public:
        Enemy(int ); //antTargets
        virtual ~Enemy();
    protected:
    private:
        int antEnemies;
        const static int MAX_HP = 100;
};

#endif // TARGET_H
