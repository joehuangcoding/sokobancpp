#include "Game.h"
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h> 
#include <cstdlib>

using namespace std;

Game::Game() {
    running = true;
    moves = 0;
    map.reset();
    player.reset(map);
}

void Game::setNonBlocking(bool enable) {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, enable ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK));
}

void Game::handleInput(char key) {
    switch (key) {
        case 'w': case 'W': player.move(-1, 0, map); moves++; break;
        case 's': case 'S': player.move(1, 0, map);  moves++; break;
        case 'a': case 'A': player.move(0, -1, map); moves++; break;
        case 'd': case 'D': player.move(0, 1, map);  moves++; break;
        case 'r': case 'R': 
            map.reset(); 
            player.reset(map); 
            moves = 0; 
            break;
        case 'q': case 'Q': running = false; break;
    }
}

void Game::run() {
    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    setNonBlocking(true);

    while (running) {
        map.draw(player.getRow(), player.getCol(), moves);

        // Check for win
        if (map.checkWin()) {
            cout << "   *** YOU WIN! ***\n";
            // cout << "   Press R to restart or Q to quit\n";

            setNonBlocking(false);
            char ch = 0;
            ssize_t n = read(STDIN_FILENO, &ch, 1);
            setNonBlocking(true);

            if (n == 1) {
                handleInput(ch);
            }
            continue;
        }

        // Read input
        char key = 0;
        if (read(STDIN_FILENO, &key, 1)) {
            handleInput(key);
        }

        usleep(30000);
    }

    // Restore terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    setNonBlocking(false);

    cout << "\nGoodbye!\n";
}
