#pragma once

#include <ncurses.h>

class Board {
  public:
    /// Constructors
    Board(WINDOW *win);

    /// Getters
    int getX() const { return this->xMax - 1; }
    int getY() const { return this->yMax - 1; }
    int getSize() const { return (this->xMax - 1) * (this->yMax - 1); }
    WINDOW *getWin() const { return this->window; }

    /// Operations
    /// @brief prints a chtype c to the board window in the position (y,x)
    /// @param y, vertical coordinate
    /// @param x, horizontal coordinate
    /// @param c, desired chtype to print
    void print(const int &y, const int &x, const chtype &c) const;

  private:
    WINDOW *window;
    int yMax, xMax;
};
