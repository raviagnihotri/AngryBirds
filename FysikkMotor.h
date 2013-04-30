#ifndef FYSIKKMOTOR_H
#define FYSIKKMOTOR_H


class FysikkMotor
{
    public:
        FysikkMotor();
        virtual ~FysikkMotor();
        float getSpeed();
        float getAngle();
        float getHeight();

        float speed;
        float angle;
        float height;
        float totalDistance;

        void totalDistanceX();
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
