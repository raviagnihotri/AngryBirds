#ifndef STAGE_H
#define STAGE_H
#include <vector>
#include <string>
using namespace std;

class Stage
{
    public:
        Stage(int, int); //hvilket stage og random startposition for enemy
        virtual ~Stage();//Velger tyngdekraft
        void setupStage();
        void setUserInput(float, float, float);  //speed, angle, height  --- setter fart, vinkel og høyde(ikke implementert funksjon)
        int getEnemyDistance();//Distansen til enemy som er satt statisk
        int getDistance_X();//Henter ut distansen til X koordinatet
        void engine();//Fysikkmotoren så vi kan se og beregne banen til fuglen med en gitt vinkel og fart
        bool gameOver();//Om enemy er ødelagt eller ikke
        bool enemyHit();//Håndterer når man treffer eller bommer på enemy
        void resetEnemyHP();//Resetter enemy HP til 100
        int getEnemyHP();
        bool getHeadshot();
        vector<string> getBird();
        vector<string> getEnemy();
        vector<float> getVector_Y();
    protected:
    private:

        void setEnemyDistance();
        int enemyDistance;
        int stage;
        int birds;
        int targets;

        float gravity;

        float speed;
        float angle;
        float height;

        float speed_X;
        float distance_X;
        float speed_Y;
        float distance_Y;
        float totalTime;
        float coord_X;
        float coord_Y;
        float time_Y;
        float time_X;
        float totalDistance;

        bool headShot;

        vector<float> vectorY;
};

#endif // STAGE_H
