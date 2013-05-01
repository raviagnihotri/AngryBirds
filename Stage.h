#ifndef STAGE_H
#define STAGE_H
#include <vector>

class Stage
{
    public:
        Stage(int); //hvilket stage
        virtual ~Stage();
        void setupStage();
        void setUserInput(float, float, float);  //speed, angle, height
        void engine();
        bool gameCheck();
        bool enemyCheck();
        vector<float> getVectory_Y(return vectorY);
    protected:
    private:
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

        bool destroyed;

        vector<float> vectorY;
};

#endif // STAGE_H
