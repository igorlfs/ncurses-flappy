#include "game.hpp"
#include "random.hpp"

#define f first
#define s second

void Game::readInput() {
    int userInputKey = wgetch(this->grid.getWin());

    switch (userInputKey) {
        case QUIT: this->gameOver = true; break;
        case ACTION: this->jumped = true; break;
    }
}

void Game::print() const {
    const matrix PIPES = this->gate.getPipes();
    const pair<int, int> BIRD = this->gate.getBird();

    // Print sky
    for (int i = 1; i <= this->grid.getX(); ++i) {
        for (int j = 1; j <= this->grid.getY(); ++j) {
            this->grid.print(j, i, SKY_CH);
        }
    }

    // Print pipes
    for (const auto &pipe : PIPES) {
        for (uint i = 1; i <= pipe.size(); ++i) {
            if (pipe[i].s) {
                this->grid.print(i, pipe[i].f, PIPE_CH);
            }
        }
    }

    // Print bird
    this->grid.print(BIRD.f, BIRD.s, BIRD_CH);

    wrefresh(this->grid.getWin());
}

void Game::update() {
    if (this->pipeGenerator % 4 == 0) {
        this->gate.spawnPipe();
    }
    this->pipeGenerator++;

    if (this->jumped) {
        this->gate.jump();
        this->jumped = false; // Reset movement
    }

    bool success = this->gate.move();

    if (!success) {
        this->gameOver = true;
    }
}

void Game::quit() {
    int yMax;
    int xMax;
    getmaxyx(stdscr, yMax, xMax);

    const string MESSAGE = "GAME OVER";
    const int SIZE = MESSAGE.size() + 2;

    WINDOW *quitWin = newwin(3, SIZE, (yMax - 3) / 2, (xMax - SIZE) / 2);

    nocbreak(); // Disables half-delay mode
    box(quitWin, 0, 0);
    mvwprintw(quitWin, 1, 1, "%s", MESSAGE.c_str());
    wgetch(quitWin);

    curs_set(1); // Display cursor again
    delwin(quitWin);
    delwin(this->grid_.GetWin());
}
