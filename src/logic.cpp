#include "logic.hpp"
#include "random.hpp"
#include <array>
#include <curses.h>

void logic::Logic::SpawnPipe() {
    // Generate random position
    const int MIN_SIZE = 3;
    const int MAX_SIZE = 5;
    const int HOLE_SIZE = Random::rng(MIN_SIZE, MAX_SIZE);
    const int PIPE_START = Random::rng(1, this->lastRow_ - HOLE_SIZE);

    vector<pair<int, bool>> pipe;

    for (int i = 0; i <= this->lastRow_; ++i) {
        if (i < PIPE_START + HOLE_SIZE && i >= PIPE_START) {
            // Empty
            pipe.emplace_back(this->lastCol_, false);
        } else {
            // Filled
            pipe.emplace_back(this->lastCol_, true);
        }
    }

    this->pipes_.push_back(pipe);
}

bool logic::Logic::Move() {
    bool hasCollided = false;

    // Try making the bird fall
    // Hitting the ground should kill the bird
    if (this->bird_.F + 1 > this->lastRow_) {
        return false;
    }

    this->bird_.F++;

    // Moves the pipes and check for a collision
    for (auto &pipe : this->pipes_) {
        for (uint i = 0; i < pipe.size(); ++i) {
            pipe[i].F--;

            // Check if bird is passing through a pipe (including a hole)
            if (pipe[i].F == Logic::kBirdCol &&
                static_cast<int>(i) == this->bird_.F) {

                // if it isn't a hole, a collision happened
                // otherwise should increase score
                if (pipe[i].S) {
                    hasCollided = true;
                } else {
                    this->score_++;
                }
            }
        }
    }

    // Remove front pipe if necessary
    if (this->pipes_.front()[0].F <= 0) {
        this->pipes_.pop_front();
    }

    return !hasCollided;
}

void logic::Logic::Jump() {
    if (this->bird_.F - kJumpHeight < 0) {
        this->bird_.F = 0;
    } else {
        this->bird_.F = this->bird_.F - kJumpHeight;
    }
}

void logic::Logic::Reset() {
    this->score_ = 0;
    this->bird_ = {this->lastRow_ / 2, Logic::kBirdCol};
    this->pipes_.clear();
}
