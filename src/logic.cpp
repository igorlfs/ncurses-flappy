#include "logic.hpp"
#include "random.hpp"
#include <array>
#include <curses.h>

#define f first
#define s second

using std::array;
using std::pair;
using std::swap;

void Logic::spawnPipe() {
    // Generate random position
    const int MIN_SIZE = 3;
    const int MAX_SIZE = 5;
    const int HOLE_SIZE = Random::rng(MIN_SIZE, MAX_SIZE);
    const int PIPE_START = Random::rng(1, this->lastRow - HOLE_SIZE);

    vector<pair<int, bool>> pipe;

    for (int i = 0; i <= this->lastRow; ++i) {
        if (i < PIPE_START + HOLE_SIZE && i > PIPE_START) {
            // Empty
            pipe.emplace_back(this->lastCol, false);
        } else {
            // Filled
            pipe.emplace_back(this->lastCol, true);
        }
    }

    this->pipes.push_back(pipe);
}

bool Logic::move() {
    bool shouldRemove = false;
    bool hasCollided = false;

    // Try making the bird fall
    // Hitting the ground should kill the bird
    if (this->bird.f + 1 > this->lastRow) {
        return false;
    }

    this->bird.f++;

    // Moves the pipes and check for a collision
    for (auto &pipe : this->pipes) {
        for (uint i = 0; i < pipe.size(); ++i) {
            pipe[i].f--;
            if (pipe[i].f <= 0) {
                shouldRemove = true;
            }
            if (pipe[i].f == this->BIRD_COL && (int)i == this->bird.f &&
                pipe[i].s) {
                hasCollided = true;
            }
        }
    }

    // Remove front pipe if necessary
    if (shouldRemove) {
        this->pipes.pop_front();
    }

    return !hasCollided;
}

void Logic::jump() {
    if (this->bird.f - JUMP_HEIGHT < 0) {
        this->bird.f = 0;
    } else {
        this->bird.f = this->bird.f - JUMP_HEIGHT;
    }
}
