#include "../include/GameOverScreen.hpp"
#include "../include/ConsoleViewport.hpp"
#include "../include/SidePanel.hpp"


GameOverScreen::GameOverScreen(const ConsoleViewport& viewport, const SidePanel& statistic)
    : height_(viewport.height()),
      width_(viewport.width()),
      isGameOver_(false),
      gameOverWin_(height_, width_, 1, 1),
      statisticWin_(gameOverWin_.derwin(height_ / 2, width_ / 2 - 2 /* <-- width indent */, height_ * 0.3, (width_ / 2) - (width_ / 2 - 2)), statistic),
      menuWin_(gameOverWin_.derwin(height_ / 2, width_ / 2 - 2 /* <-- width indent */, height_ * 0.3, width_ / 2), *this)
{}

void GameOverScreen::render() {
    gameOverWin_.wclear();
    gameOverWin_.box();
    gameOverWin_.printAt(height_ * 0.2, width_ / 2 - 5, "Game Over");
    gameOverWin_.wrefresh();
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
    statisticWin_.box();
    statisticWin_.printAt(1, width_ / 2 - 5, "Statistic:");
    statisticWin_.printAt(2, 1, "Score: %d", score_);
    // statisticWin_.printAt(3, 1, "Level: %d", level_);
    statisticWin_.wrefresh();
}

GameOverScreen::MenuWindow::MenuWindow(ncui::Window menuWin, GameOverScreen& owner)
    : menuWin_(std::move(menuWin)),
      height_(menuWin_.height()),
      width_(menuWin_.width()),
      owner_(owner)
{}

void GameOverScreen::MenuWindow::render() {
    menuWin_.box();
    menuWin_.printAt(1, width_ / 2 - 5, "Main menu");
    menuWin_.setKeypad(true);

    int ch;
    while (true) {
        for (int i = 0; i < menuPoints_; ++i) {
            if (i == selectedPoint_)
                menuWin_.attrOn(A_REVERSE);
            menuWin_.printAt(2 + i, 2, "%s", menuItems_[i]);
            menuWin_.attrOff(A_REVERSE);
        }
        menuWin_.wrefresh();

        ch = menuWin_.getKey();
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