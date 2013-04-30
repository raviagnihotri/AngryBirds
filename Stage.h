#ifndef STAGE_H
#define STAGE_H


class Stage
{
    public:
        Stage(int, int, float);  //birds,targets,gravity
        int getBirds();
        int getTargets();
        float getGravity();

        void settingsGame(); //speed, angle
        virtual ~Stage();
    protected:
    private:
        int birds;
        int targets;
        float gravity;
        int speed;
        int angle;
};

#endif // STAGE_H
