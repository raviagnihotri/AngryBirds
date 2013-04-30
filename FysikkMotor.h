#ifndef FYSIKKMOTOR_H
#define FYSIKKMOTOR_H


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

        float speed;
        float angle;
        float height;
        float totalDistance;

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
