#pragma once

#include "board.hpp"
#include "logic.hpp"
#include <ncurses.h>
#include <string>

using std::string;

class Game {
  public:
    /// Constructors
    Game(WINDOW *win) : grid(win), gate(win->_maxx - 1, win->_maxy - 1) {}

    /// Getters
    bool isGameOver() const { return this->gameOver; }

    /// Operations

    /// @brief reads user input
    void readInput();

    /// @brief update game based on input
    void update();

    /// @brief print changes in memory to screen
    void print() const;

    /// @brief print a game over message and quit
    static void quit();

  private:
    bool gameOver{false};
    bool jumped{false};

    Board grid;
    Logic gate;

    /// Actions
    static constexpr int QUIT{(int)'x'};
    static constexpr int ACTION{(int)' '};
    /// Printable chars
    static constexpr int BIRD{(int)'*'};
    static constexpr int PIPE{(int)'|'};
};
