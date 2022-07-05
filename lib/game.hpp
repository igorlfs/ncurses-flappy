#pragma once

#include "board.hpp"
#include "logic.hpp"
#include <ncurses.h>
#include <string>

namespace game {

using std::string;

#define F first
#define S second

class Flappy {
  public:
    /// Constructors
    explicit Flappy(WINDOW *win)
        : grid_(win), gate_({win->_maxx - 1, win->_maxy - 1}) {
        init_pair(1, COLOR_RED, COLOR_YELLOW);
        init_pair(2, COLOR_GREEN, COLOR_GREEN);
        init_pair(3, -1, COLOR_CYAN);
    }

    /// Getters

    bool IsGameOver() const { return this->gameOver_; }

    /// Operations

    /// @brief reads user input
    void ReadInput();

    /// @brief update game based on input
    void Update();

    /// @brief print changes in memory to screen
    void Print() const;

    /// @brief print a game over message and quit
    /// @return true if the game should continue
    bool Quit();

    /// @brief reset game state so a new run can be started
    void Reset();

  private:
    bool gameOver_{false};
    bool jumped_{false};
    int pipeGenerator_{0};

    Board grid_;
    logic::Logic gate_;

    /// Actions
    static constexpr int kQuit{static_cast<int>('x')};
    static constexpr int kAction{static_cast<int>(' ')};
    static constexpr int kReset{static_cast<int>('r')};

    /// Printable chars
    static constexpr chtype kBirdCh = '*' | A_BOLD | COLOR_PAIR(1);
    static constexpr int kPipeCh = '$' | A_BOLD | COLOR_PAIR(2);
    static constexpr int kSkyCh = ' ' | A_BOLD | COLOR_PAIR(3);
};

} // namespace game
