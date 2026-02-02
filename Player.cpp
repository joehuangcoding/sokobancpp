#include "Player.h"

Player::Player() : row(0), col(0) {}

void Player::reset(const Map& map) {
    map.findPlayer(row, col);
}

void Player::move(int dr, int dc, Map& map) {
    int new_r = row + dr;
    int new_c = col + dc;
    if (!map.canMove(row, col, dr, dc)) return;
    if (map.isBox(new_r, new_c)) {
        int box_r = new_r + dr;
        int box_c = new_c + dc;
        char box_target = map.isGoal(box_r, box_c) ? '*' : 'o';
        map.set(box_r, box_c, box_target);
        map.set(new_r, new_c, map.isGoal(new_r, new_c) ? '.' : ' ');
    }
    map.set(row, col, map.isGoal(row, col) ? '.' : ' ');
    row = new_r;
    col = new_c;
}
