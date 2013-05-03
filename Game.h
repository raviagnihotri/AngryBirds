#ifndef GAME_H
#define GAME_H


class Game
{
    private:
        void initLogo();
        void initSun();
        void initScreen();
        void welcomeScr();
        void userInput();
        void startStage(int i);
        void finish();
        int stagePick;
    public:
        Game();
        virtual ~Game();
        int speed;
        int angle;
};

#endif // GAME_H
