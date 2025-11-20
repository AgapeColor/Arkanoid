#include "../include/GameWindow.hpp"
#include "../include/ConsoleViewport.hpp"

GameWindow::GameWindow(const ConsoleViewport& viewport) 
    : height_(viewport.height()),
      width_(viewport.width()),
      gameWin_(height_, width_, 1, 1),
      sidePanel_(gameWin_.derwin(height_ / 3, width_ / 3, height_ / 3, (width_ / 3) / 2)),
      field_(gameWin_.derwin(height_ - 2, width_ / 2.2, 1, width_ / 2))
{}

void GameWindow::render() {
    gameWin_.wrefresh();
    sidePanel_.render();
    field_.render();
}

void GameWindow::reset() {
    gameWin_.wclear();
    gameWin_.box();
    gameWin_.wrefresh();
    sidePanel_.reset();
    field_.reset();
}