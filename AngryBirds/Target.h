#ifndef TARGET_H
#define TARGET_H


class Target
{
    public:
        Target(int ); //antTargets
        virtual ~Target();
    protected:
    private:
        int antTargets;
        const static int MAX_HP = 100;
        char graphic[3] = {'a', 'b', 'c'};
};

#endif // TARGET_H
