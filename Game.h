#pragma once
#include "Map.h"
#include "Player.h"

class Game {
public:
    Game();

    // Start the game loop
    void run();

private:
    Map map;
    Player player;
    bool running;
    int moves;

    // Non-blocking terminal input
    void setNonBlocking(bool enable);

    // Handle key input
    void handleInput(char key);
};
