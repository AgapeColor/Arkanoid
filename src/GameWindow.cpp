#include "../include/GameWindow.hpp"
#include "../include/ConsoleViewport.hpp"

GameWindow::GameWindow(const ConsoleViewport &viewport) 
    : height_(viewport.height()),
      width_(viewport.width()),
      gameWin_(newwin(height_, width_, 1, 1)),
      sidePanel_(height_ / 3, width_ / 3, gameWin_),
      field_(height_ - 2, width_ / 2.2, gameWin_, width_)
{}

GameWindow::~GameWindow() {
  delwin(gameWin_);
}

void GameWindow::render() {
  wrefresh(gameWin_);
  sidePanel_.render();
  field_.render();
}

void GameWindow::reset() {
  wclear(gameWin_);
  box(gameWin_, 0, 0);
  wrefresh(gameWin_);
  sidePanel_.reset();
  field_.reset();
}