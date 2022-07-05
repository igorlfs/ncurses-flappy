#include "game.hpp"
#include "random.hpp"

using std::pair;

void game::Flappy::ReadInput() {
    int userInputKey = wgetch(this->grid_.GetWin());

    switch (userInputKey) {
        case kQuit: this->gameOver_ = true; break;
        case kAction: this->jumped_ = true; break;
        case kReset: Reset(); break;
    }
}

void game::Flappy::Print() const {
    const logic::matrix PIPES = this->gate_.GetPipes();
    const pair<int, int> BIRD = this->gate_.GetBird();

    // Print sky
    for (int i = 1; i <= this->grid_.GetX(); ++i) {
        for (int j = 1; j <= this->grid_.GetY(); ++j) {
            this->grid_.Print(j, i, kSkyCh);
        }
    }

    // Print pipes
    for (const auto &pipe : PIPES) {
        for (uint i = 1; i <= pipe.size(); ++i) {
            if (pipe[i].S) {
                this->grid_.Print(static_cast<int>(i), pipe[i].F, kPipeCh);
            }
        }
    }

    // Print bird
    this->grid_.Print(BIRD.F, BIRD.S, kBirdCh);

    wrefresh(this->grid_.GetWin());
}

void game::Flappy::Update() {
    if (this->pipeGenerator_ % 4 == 0) {
        this->gate_.SpawnPipe();
    }
    this->pipeGenerator_++;

    if (this->jumped_) {
        this->gate_.Jump();
        this->jumped_ = false; // Reset movement
    }

    bool success = this->gate_.Move();

    if (!success) {
        this->gameOver_ = true;
    }
}

bool game::Flappy::Quit() {
    const int SCORE = this->gate_.GetScore();

    int yMax;
    int xMax;
    getmaxyx(stdscr, yMax, xMax);

    const string MESSAGE = "GAME OVER";
    const int M_SIZE = static_cast<int>(MESSAGE.size()) + 2;

    // This only works because M_SIZE > lenght("SCORE: score_")
    WINDOW *quitWin = newwin(4, M_SIZE, (yMax - 3) / 2, (xMax - M_SIZE) / 2);

    box(quitWin, 0, 0);
    mvwprintw(quitWin, 1, 1, "%s", MESSAGE.c_str());
    mvwprintw(quitWin, 2, 1, "SCORE: %d", SCORE);
    wrefresh(quitWin);

    int input = getch();
    if (input == kReset) {
        Reset();
    }

    delwin(quitWin);

    return input != kReset;
}

void game::Flappy::Reset() {
    this->gameOver_ = false;
    this->gate_.Reset();
};
