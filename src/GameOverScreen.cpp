#include "../include/GameOverScreen.hpp"
#include "../include/ConsoleViewport.hpp"
#include "../include/SidePanel.hpp"

GameOverScreen::GameOverScreen(const ConsoleViewport &viewport, const SidePanel& statistic)
  : height_(viewport.height()),
    width_(viewport.width()),
    isGameOver_(false),
    gameOverWin_(newwin(height_, width_, 1, 1)),
    statisticWin_(height_, width_, gameOverWin_, statistic),
    menuWin_(height_, width_, gameOverWin_, *this)
{}

GameOverScreen::~GameOverScreen() {
  delwin(gameOverWin_);
}

void GameOverScreen::render() {
  wclear(gameOverWin_);
  box(gameOverWin_, 0, 0);
  mvwprintw(gameOverWin_, height_ * 0.2, width_ / 2 - 5, "Game Over");
  wrefresh(gameOverWin_);
  statisticWin_.render();
  menuWin_.render();
}

GameOverScreen::StatisticWindow::StatisticWindow(int height, int width, WINDOW* parent, const SidePanel& statistic)
  : height_(height / 2),
    width_(width / 2 - 2 /* <-- width indent */),
    score_(statistic.score()),
    level_(statistic.level()),
    win_(derwin(parent, height_, width_, height * 0.3, (width / 2) - width_))
{}

GameOverScreen::StatisticWindow::~StatisticWindow() {
  delwin(win_);
}

void GameOverScreen::StatisticWindow::render() {
  box(win_, 0, 0);
  mvwprintw(win_, 1, width_ / 2 - 5, "Statistic:");
  mvwprintw(win_, 2, 1, "Score: %d", score_);
  mvwprintw(win_, 3, 1, "Level: %d", level_);
  wrefresh(win_);
}

GameOverScreen::MenuWindow::MenuWindow(int height, int width, WINDOW* parent, GameOverScreen& owner)
  : height_(height / 2),
    width_(width / 2 - 2 /* <-- width indent */),
    win_(derwin(parent, height_, width_, height * 0.3, width / 2)),
    owner_(owner)
{}

GameOverScreen::MenuWindow::~MenuWindow() {
  delwin(win_);
}

void GameOverScreen::MenuWindow::render() {
  box(win_, 0, 0);
  mvwprintw(win_, 1, width_ / 2 - 5, "Main menu");
  keypad(win_, true);
  
  int ch;
  while (true) {
    for (int i = 0; i < menuPoints_; ++i) {
      if (i == selectedPoint_)
        wattron(win_, A_REVERSE);
      mvwprintw(win_, 2 + i, 2, "%s", menuItems_[i]);
      wattroff(win_, A_REVERSE);
    }
    wrefresh(win_);
  
    ch = wgetch(win_);
    switch (ch) {
      case KEY_UP:
        selectedPoint_ = (selectedPoint_ - 1 + menuPoints_) % menuPoints_;
        break;
      case KEY_DOWN:
        selectedPoint_ = (selectedPoint_ + 1) % menuPoints_;
        break;
      case '\n':
        if (selectedPoint_ == 1)
          owner_.isGameOver_ = true;
        return;
    }
  }
}