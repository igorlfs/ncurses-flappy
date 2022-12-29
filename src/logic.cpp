#include "logic.hpp"
#include "random.hpp"

void logic::Logic::SpawnPipe() {
    // Generate random position
    const int MIN_SIZE = 3;
    const int MAX_SIZE = 5;
    const ulong HOLE_SIZE = Random::Rng(MIN_SIZE, MAX_SIZE);
    const ulong PIPE_START = Random::Rng(1, this->lastRow_ - HOLE_SIZE);

    pair<int, vector<bool>> pipe;
    pipe.first = this->lastCol_;

    for (ulong i = 0; i < this->lastRow_; ++i) {
        if (i < PIPE_START + HOLE_SIZE && i >= PIPE_START) {
            // Empty
            pipe.second.push_back(false);
        } else {
            // Filled
            pipe.second.push_back(true);
        }
    }

    this->pipes_.push_back(pipe);
}

bool logic::Logic::Move() {
    bool hasCollided = false;

    // Try making the bird fall
    // Hitting the ground should kill the bird
    if (this->birdHeight_ + 1 > this->lastRow_) {
        return false;
    }

    this->birdHeight_++;

    // Moves the pipes and check for a collision
    for (auto &pipe : this->pipes_) {
        pipe.F--;

        // Check if bird is passing through a pipe
        if (pipe.F == Logic::kBirdCol) {
            // if it isn't a hole, a collision happened
            // otherwise should increase score
            if (pipe.S[this->birdHeight_ - 1]) {
                hasCollided = true;
            } else {
                this->score_++;
            }
        }
    }

    // Remove front pipe if necessary
    if (this->pipes_.front().F <= 0) {
        this->pipes_.pop_front();
    }

    return !hasCollided;
}

void logic::Logic::Jump() {
    if (this->birdHeight_ - kJumpHeight < 0) {
        this->birdHeight_ = 0;
    } else {
        this->birdHeight_ = this->birdHeight_ - kJumpHeight;
    }
}

void logic::Logic::Reset() {
    this->score_ = 0;
    this->birdHeight_ = this->lastRow_ / 2;
    this->pipes_.clear();
}
