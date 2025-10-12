#include "../include/GameOverScreen.hpp"
#include "../include/ConsoleViewport.hpp"
#include "../include/SidePanel.hpp"


GameOverScreen::GameOverScreen(const ConsoleViewport &viewport, const SidePanel& statistic)
  : height_(viewport.height()),
    width_(viewport.width()),
    isGameOver_(false),
    gameOverWin_(height_, width_, 1, 1),
    statisticWin_(gameOverWin_.derwin(height_ / 2, width_ / 2 - 2 /* <-- width indent */, height_ * 0.3, (width_ / 2) - (width_ / 2 - 2)), statistic),
    menuWin_(gameOverWin_.derwin(height_ / 2, width_ / 2 - 2 /* <-- width indent */, height_ * 0.3, width_ / 2), *this)
{}

void GameOverScreen::render() {
  wclear(gameOverWin_.get());
  box(gameOverWin_.get(), 0, 0);
  mvwprintw(gameOverWin_.get(), height_ * 0.2, width_ / 2 - 5, "Game Over");
  wrefresh(gameOverWin_.get());
  statisticWin_.render();
  menuWin_.render();
}

GameOverScreen::StatisticWindow::StatisticWindow(ncui::Window statisticWin, const SidePanel& statistic)
  : statisticWin_(std::move(statisticWin)),
    height_(statisticWin.height()),
    width_(statisticWin.width()),
    score_(statistic.score()),
    level_(statistic.level())
{}

void GameOverScreen::StatisticWindow::render() {
  box(statisticWin_.get(), 0, 0);
  mvwprintw(statisticWin_.get(), 1, width_ / 2 - 5, "Statistic:");
  mvwprintw(statisticWin_.get(), 2, 1, "Score: %d", score_);
  mvwprintw(statisticWin_.get(), 3, 1, "Level: %d", level_);
  wrefresh(statisticWin_.get());
}

GameOverScreen::MenuWindow::MenuWindow(ncui::Window menuWin, GameOverScreen& owner)
  : menuWin_(std::move(menuWin)),
    height_(menuWin_.height()),
    width_(menuWin_.width()),
    owner_(owner)
{}

void GameOverScreen::MenuWindow::render() {
  box(menuWin_.get(), 0, 0);
  mvwprintw(menuWin_.get(), 1, width_ / 2 - 5, "Main menu");
  keypad(menuWin_.get(), true);

  int ch;
  while (true) {
    for (int i = 0; i < menuPoints_; ++i) {
      if (i == selectedPoint_)
        wattron(menuWin_.get(), A_REVERSE);
      mvwprintw(menuWin_.get(), 2 + i, 2, "%s", menuItems_[i]);
      wattroff(menuWin_.get(), A_REVERSE);
    }
    wrefresh(menuWin_.get());

    ch = wgetch(menuWin_.get());
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