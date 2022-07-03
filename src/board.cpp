#include "board.hpp"

Board::Board(WINDOW *win) : window(win), yMax(win->_maxy), xMax(win->_maxx) {
    box(this->window, 0, 0);
    wrefresh(this->window);
    keypad(this->window, true);
    leaveok(this->window, true);
}

void Board::print(const int &y, const int &x, const chtype &c) const {
    mvwaddch(this->window, y, x, c);
}
