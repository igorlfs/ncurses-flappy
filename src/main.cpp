#include "game.hpp"
#include "msgassert.hpp"

static constexpr int WINDOW_COLS = 12;
static constexpr int WINDOW_ROWS = 18;

// TODO:
// - Track Score (print when quitting)
// - Tests

void initialize() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();
    assert(has_colors(), "No color support!");
    start_color();
    use_default_colors();
}

WINDOW *centralizeWindow() {
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);

    return newwin(WINDOW_COLS, WINDOW_ROWS, (yMax - WINDOW_COLS) / 2,
                  (xMax - WINDOW_ROWS) / 2);
}

int main() {
    initialize();

    WINDOW *gameWindow = centralizeWindow();
    Game game(gameWindow);

    const int DELAY = 2;
    halfdelay(DELAY);

    while (!game.isGameOver()) {
        game.print();
        game.readInput();
        game.update();
    }

    Game::quit();
    endwin();
}
