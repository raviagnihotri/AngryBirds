#ifndef TARGET_H
#define TARGET_H


class Target
{
    public:
        Target();
        virtual ~Target();
    protected:
    private:
        int healthPoints;
        int graphic;
};

#endif // TARGET_H
