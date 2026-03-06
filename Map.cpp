#include "Map.h"
#include <cstdlib>

using namespace std;

Map::Map() {
    reset();
}

void Map::reset() {
    memcpy(grid, ORIGINAL_LEVEL, sizeof(ORIGINAL_LEVEL));
}

void Map::draw(int player_r, int player_c, int moves) const {
    int ignore = system("clear");
    (void)ignore;
    cout << "  SOKOBAN   (WASD = move,  R = restart,  Q = quit)\n";
    cout << "  Moves: " << moves << "\n\n";

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            char ch = grid[r][c];
            if (r == player_r && c == player_c)
                cout << 'P';
            else
                cout << ch;
        }
        cout << '\n';
    }
    cout << '\n';
}

bool Map::canMove(int r, int c, int dr, int dc) const {
    int nr = r + dr;
    int nc = c + dc;
    if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) return false;
    char next = grid[nr][nc];
    if (next == '#') return false; // wall
    if (next == 'o' || next == '*') {
        //Next next
        int nnr = nr + dr;
        int nnc = nc + dc;
        if (nnr < 0 || nnr >= ROWS || nnc < 0 || nnc >= COLS) return false;
        char behind = grid[nnr][nnc];
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
