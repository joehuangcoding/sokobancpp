#pragma once
#include "Map.h"

class Player {
public:
    Player();
    void reset(const Map& map);
    void move(int dr, int dc, Map& map);
    int getRow() const { return row; }
    int getCol() const { return col; }
    
private:
    int row;
    int col;
};
