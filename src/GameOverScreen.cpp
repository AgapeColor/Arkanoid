#include "../include/GameOverScreen.hpp"
#include "../include/ConsoleViewport.hpp"


GameOverScreen::GameOverScreen(const ConsoleViewport& viewport)
    : height_(viewport.height()),
      width_(viewport.width()),
      isGameOver_(false),
      gameOverWin_(height_, width_, 1, 1),  // Position at y = 1, x = 1 (1 - cell offset)
      statisticWin_(gameOverWin_.derwin(height_ / WINDOW_HEIGHT_DIVISOR,
                                        width_ / WINDOW_WIDTH_DIVISOR - WINDOW_WIDTH_INDENT,
                                        height_ * WINDOW_Y_POSITION,
                                        (width_ / WINDOW_WIDTH_DIVISOR) - (width_ / WINDOW_WIDTH_DIVISOR - WINDOW_WIDTH_INDENT))),

      menuWin_(gameOverWin_.derwin(height_ / WINDOW_HEIGHT_DIVISOR,
                                   width_ / WINDOW_WIDTH_DIVISOR - WINDOW_WIDTH_INDENT,
                                   height_ * WINDOW_Y_POSITION,
                                   width_ / WINDOW_WIDTH_DIVISOR),
                                   *this)
{}

void GameOverScreen::render(int score) {
    gameOverWin_.wclear();
    gameOverWin_.box();
    gameOverWin_.printAt(height_ * TITLE_Y_POSITION, width_ / WINDOW_WIDTH_DIVISOR - TITLE_X_OFFSET, "Game Over");
    gameOverWin_.wrefresh();
    statisticWin_.render(score);
    menuWin_.render();
}

GameOverScreen::StatisticWindow::StatisticWindow(ncui::Window statisticWin)
    : statisticWin_(std::move(statisticWin)),
      height_(statisticWin_.height()),
      width_(statisticWin_.width())
{}

void GameOverScreen::StatisticWindow::render(int score) {
    statisticWin_.box();
    statisticWin_.printAt(1, width_ / WINDOW_WIDTH_DIVISOR - TITLE_X_OFFSET, "Statistic");
    statisticWin_.printAt(2, 2, "Score: %d", score);
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
    menuWin_.printAt(1, width_ / WINDOW_WIDTH_DIVISOR - TITLE_X_OFFSET, "Main menu");
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
