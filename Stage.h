#ifndef STAGE_H
#define STAGE_H
#include <vector>
#include <string>
using namespace std;

class Stage
{
    public:
        Stage(int); //hvilket stage
        virtual ~Stage();
        void setupStage();
        void setUserInput(float, float, float);  //speed, angle, height
        int getEnemyDistance();
        int getDistance_X();
        void engine();
        bool gameOver();
        bool enemyHit();
        void resetEnemyHP();
        int getEnemyHP();
        vector<string> getBird();
        vector<float> getVector_Y();
    protected:
    private:

        int enemyDistance = 140;
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

        vector<float> vectorY;
};

#endif // STAGE_H
