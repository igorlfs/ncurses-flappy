#pragma once

#include <list>
#include <vector>

using std::list;
using std::pair;
using std::vector;

using matrix = list<vector<pair<int, bool>>>;

class Logic {
  public:
    /// Constructors
    Logic(const int &_lastCol, const int &_lastRow)
        : lastCol(_lastCol), lastRow(_lastRow) {
        this->bird = {this->lastRow / 2, this->BIRD_COL};
    }

    /// Getters
    matrix getPipes() const { return this->pipes; }
    pair<int, int> getBird() const { return this->bird; }

    /// Operations

    /// @brief creates a new pipe and sent it to the last column
    void spawnPipe();

    /// @brief handle jump movement
    void jump();

    /// @brief moves pipes and make bird fall
    bool move();

  private:
    const int BIRD_COL{4};
    const int JUMP_HEIGHT{3};
    int lastCol;
    int lastRow;

    matrix pipes;
    pair<int, int> bird;
};
