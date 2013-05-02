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
    public:
        Game();
        virtual ~Game();
};

#endif // GAME_H
