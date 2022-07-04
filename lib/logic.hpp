#pragma once

#include <list>
#include <vector>

namespace logic {

using std::list;
using std::pair;
using std::vector;

#define F first
#define S second

using matrix = list<vector<pair<int, bool>>>;

class Logic {
  public:
    /// Constructors
    explicit Logic(const pair<int, int> &last)
        : lastCol_(last.F), lastRow_(last.S) {
        this->bird_ = {this->lastRow_ / 2, Logic::kBirdCol};
    }

    /// Getters
    matrix GetPipes() const { return this->pipes_; }
    pair<int, int> GetBird() const { return this->bird_; }
    int GetScore() const { return this->score_; }

    /// Operations

    /// @brief creates a new pipe and sent it to the last column
    void SpawnPipe();

    /// @brief handle jump movement
    void Jump();

    /// @brief moves pipes and make bird fall
    bool Move();

  private:
    static constexpr int kBirdCol{4};
    static constexpr int kJumpHeight{3};

    int score_{-1};
    int lastCol_;
    int lastRow_;

    matrix pipes_;
    pair<int, int> bird_;
};

} // namespace logic
