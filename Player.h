#pragma once
#include "Map.h"

class Player {
    private:
        int row;
        int col;
    public:
        Player();
        void reset(const Map& map);
        void move(int dr, int dc, Map& map);
        int getRow() const { return row; }
        int getCol() const { return col; }
};
