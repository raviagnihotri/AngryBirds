#ifndef FYSIKKMOTOR_H
#define FYSIKKMOTOR_H
#include <vector>
using namespace std;


class FysikkMotor
{
    public:
        FysikkMotor(float, float, float);
        virtual ~FysikkMotor();
        float coord_X;
        float coord_Y;
        float time_Y;
        float time_X;
        float getSpeed();
        float getAngle();
        float getHeight();
        void setCoord_X(float);
        void setCoord_Y(float);
        float getCoord_X();
        float getCoord_Y();

        float speed_X;
        float distance_X;
        float speed_Y;
        float distance_Y;
        float totalTime;

        float speed;
        float angle;
        float height;
        float totalDistance;

        vector<float> vectorX;
        vector<float> vectorY;
        void engine();
//        int sinSpeed;
//        int cosSpeed;
//        int timeY;
//        int timeYHeight;
//        int distanceYHeight;
//        int totalHeight;
//        int timeYDown;
//        int totalTime;
//        int totalDistanceX;
    protected:
    private:
};

#endif // FYSIKKMOTOR_H
