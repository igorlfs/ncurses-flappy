#include "game.hpp"
#include "msgassert.hpp"

static constexpr int kWindowCols = 12;
static constexpr int kWindowRows = 18;

// TODO(igorlfs):
// - Tests

void Initialize() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();
    assert(has_colors(), "No color support!");
    start_color();
    use_default_colors();
}

WINDOW *CentralizeWindow() {
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);

    return newwin(kWindowCols, kWindowRows, (yMax - kWindowCols) / 2,
                  (xMax - kWindowRows) / 2);
}

int main() {
    Initialize();

    WINDOW *gameWindow = CentralizeWindow();
    game::Flappy game(gameWindow);

    const int DELAY = 200;
    wtimeout(gameWindow, DELAY);

reset:

    while (!game.IsGameOver()) {
        game.Print();
        game.ReadInput();
        game.Update();
    }

    if (!game.Quit()) {
        goto reset;
    }

    delwin(gameWindow);
    endwin();
}
