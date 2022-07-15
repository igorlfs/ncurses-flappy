#pragma once

#include <list>
#include <vector>

namespace logic {

using std::list;
using std::pair;
using std::vector;

#define F first
#define S second

class Logic {
  public:
    /// Constructors
    explicit Logic(const pair<int, int> &last)
        : lastCol_(last.F), lastRow_(last.S) {
        this->birdHeight_ = this->lastRow_ / 2;
    }

    /// Getters
    auto GetPipes() const { return this->pipes_; }
    pair<int, int> GetBird() const {
        return {this->birdHeight_, Logic::kBirdCol};
    }
    int GetScore() const { return this->score_; }

    /// Operations

    /// @brief creates a new pipe and sent it to the last column
    void SpawnPipe();

    /// @brief handle jump movement
    void Jump();

    /// @brief moves pipes and make bird fall
    bool Move();

    /// @brief reset game state
    void Reset();

  private:
    static constexpr int kBirdCol{4};
    static constexpr int kJumpHeight{3};

    int score_{0};
    int lastCol_;
    int lastRow_;

    list<pair<int, vector<bool>>> pipes_;
    int birdHeight_;
};

} // namespace logic
