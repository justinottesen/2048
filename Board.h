#ifndef __BOARD_H
#define __BOARD_H

#include <cstdlib>
#include <ctime>
#include <cassert>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

class Board {
  public:
    Board();

    void up();
    void down();
    void left();
    void right();

    unsigned int getScore() const { return score; }
    void print(std::ostream& ostr) const;
    bool checkStatus() const; // true = Continue, false = Game Over

  private:
    void add(unsigned int num = 1);
    bool won() const;

    int board[4][4];
    int score;
};

#endif