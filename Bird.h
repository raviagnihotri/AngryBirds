#ifndef BIRD_H
#define BIRD_H


class Bird
{
    public:
        Bird(int);
        virtual ~Bird();
        void setSpeed(int);
        int getSpeed();
        int getWeight();
    protected:
    private:
        int speed;
        int weight;
};

#endif // BIRD_H
