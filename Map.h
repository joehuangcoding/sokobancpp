#pragma once
#include <iostream>
#include <cstring> // for memcpy

const int ROWS = 12;
const int COLS = 21;

class Map {
public:
    Map();

    void reset();

    void draw(int player_r, int player_c, int moves) const;

    bool canMove(int r, int c, int dr, int dc) const;

    bool isGoal(int r, int c) const;

    bool isBox(int r, int c) const;

    void set(int r, int c, char value);

    void findPlayer(int &out_r, int &out_c) const;

    bool checkWin() const;

private:
    char grid[ROWS][COLS];
    static constexpr char ORIGINAL_LEVEL[ROWS][COLS] = {
        "####################",
        "#                  #",
        "#  ### ###  ####   #",
        "#  #     #  #  #   #",
        "#     o  #  #      #",
        "#  #     ####  ### #",
        "#  ### ###     #   #",
        "#     P            #",
        "#  ### ###  ####   #",
        "#  #     #  #  #   #",
        "#          .       #",
        "####################"
    };
};
