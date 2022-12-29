#pragma once

#include "board.hpp"
#include "logic.hpp"
#include <curses.h>
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
        // avoid clangd's [readability-magic-numbers]
        init_pair(3 + 1, COLOR_RED, COLOR_MAGENTA);
        init_pair(3 + 2, COLOR_RED, COLOR_RED);
        init_pair(3 + 3, -1, COLOR_BLACK);
        UpdatesColors();
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

    /// @brief (easter egg) updates colors
    void UpdatesColors();

  private:
    bool gameOver_{false};
    bool jumped_{false};
    bool colors_{false};
    int pipeGenerator_{0};

    Board grid_;
    logic::Logic gate_;

    /// Actions
    static constexpr int kQuit{static_cast<int>('x')};
    static constexpr int kAction{static_cast<int>(' ')};
    static constexpr int kReset{static_cast<int>('r')};
    static constexpr int kToggleColors{static_cast<int>('t')};

    /// Printable chars
    chtype skyChar_;
    chtype birdChar_;
    chtype pipeChar_;
};

} // namespace game
