#ifndef STAGE_H
#define STAGE_H


class Stage
{
    public:
        Stage();
        virtual ~Stage();
    protected:
    private:
        int birds[];
        int targets[];
        int gravity;
};

#endif // STAGE_H
