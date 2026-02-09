#include <ncurses.h>
#include <stdexcept>
#include <algorithm>
#include "../include/ConsoleViewport.hpp"

ConsoleViewport::ConsoleViewport(int marginY, int marginX)
    : rows_(0),
      cols_(0),
      marginY_(marginY),
      marginX_(marginX)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    detectWindowSize();
}

ConsoleViewport::~ConsoleViewport() {
    endwin();
}

void ConsoleViewport::detectWindowSize() {
    int rawRows, rawCols;
    getmaxyx(stdscr, rawRows, rawCols);
    if (rawRows < 1 || rawCols < 1) {
        throw std::runtime_error("ConsoleViewport: invalid window size");
    }
    rows_ = std::max(1, rawRows - (2 * marginY_));
    cols_ = std::max(1, rawCols - (3 * marginX_));
}

void ConsoleViewport::initialize() const {
    clear();
    box(stdscr, 0, 0);
    refresh();
 }

