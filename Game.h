#pragma once
#include "Map.h"
#include "Player.h"
#include "LEDBlink.h"
class Game {
    public:
        Game();
        void run();

    private:
        Map map;
        Player player;
        LEDBlink ledBlinkCtl;
        bool running;
        int moves;

        void setNonBlocking(bool enable);
        void handleInput(char key);
};
