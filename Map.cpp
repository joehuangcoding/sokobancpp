#include "Map.h"
#include <cstdlib>

Map::Map() {
    reset();
}

void Map::reset() {
    std::memcpy(grid, ORIGINAL_LEVEL, sizeof(ORIGINAL_LEVEL));
}

void Map::draw(int player_r, int player_c, int moves) const {
    int ignore = std::system("clear");
    (void)ignore;
    std::cout << "  SOKOBAN   (WASD = move,  R = restart,  Q = quit)\n";
    std::cout << "  Moves: " << moves << "\n\n";

    for (int r = 0; r < ROWS; ++r) {
        // for (int c = 0; c < COLS; ++c) {
        //     char ch = grid[r][c];
        //     if (r == player_r && c == player_c) std::cout << "\033[1;33m☻\033[0m"; // player
        //     else if (ch == 'o') std::cout << "\033[1;37mo\033[0m";    // box
        //     else if (ch == '*') std::cout << "\033[1;32m◎\033[0m";    // box on goal
        //     else if (ch == '.') std::cout << "\033[1;32m.\033[0m";    // goal
        //     else if (ch == '#') std::cout << "\033[1;90m█\033[0m";    // wall
        //     else std::cout << ch;                                      // empty space
        // }
        for (int c = 0; c < COLS; ++c) {
            char ch = grid[r][c];

            // Highlight the player position
            if (r == player_r && c == player_c)
                std::cout << 'P';
            else
                std::cout << ch;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

bool Map::canMove(int r, int c, int dr, int dc) const {
    int nr = r + dr;
    int nc = c + dc;

    if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) return false;

    char next = grid[nr][nc];

    if (next == '#') return false; // wall

    // Box push?
    if (next == 'o' || next == '*') {
        int br = nr + dr;
        int bc = nc + dc;

        if (br < 0 || br >= ROWS || bc < 0 || bc >= COLS) return false;
        char behind = grid[br][bc];
        if (behind == '#' || behind == 'o' || behind == '*') return false;
    }

    return true;
}


bool Map::isGoal(int r, int c) const {
    char ch = grid[r][c];
    return ch == '.' || ch == '*';
}

bool Map::isBox(int r, int c) const {
    char ch = grid[r][c];
    return ch == 'o' || ch == '*';
}

void Map::set(int r, int c, char value) {
    grid[r][c] = value;
}

void Map::findPlayer(int &out_r, int &out_c) const {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (grid[r][c] == 'P') {
                out_r = r;
                out_c = c;
                return;
            }
        }
    }
}

bool Map::checkWin() const {
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS; ++c)
            if (grid[r][c] == '.') return false;
    return true;
}
