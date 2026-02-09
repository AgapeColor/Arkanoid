#include "../include/GameWinScreen.hpp"
#include "../include/ConsoleViewport.hpp"


GameWinScreen::GameWinScreen(const ConsoleViewport& viewport)
    : height_(viewport.height()),
      width_(viewport.width()),
      isGameWin_(false),
      gameWinWin_(height_, width_, 1, 1),  // Position at y = 1, x = 1 (1 - cell offset)
      menuWin_(gameWinWin_.derwin(MENU_HEIGHT, MENU_WIDTH,
                                  height_ * WINDOW_Y_POSITION,
                                  width_ / WINDOW_WIDTH_DIVISOR - (MENU_WIDTH / WINDOW_WIDTH_DIVISOR)),
                                  *this)
{}

void GameWinScreen::render(int score) {
    gameWinWin_.wclear();
    gameWinWin_.box();
    gameWinWin_.printAt(height_ * TITLE_Y_POSITION, width_ / WINDOW_WIDTH_DIVISOR - TITLE_X_OFFSET, "You win!");
    gameWinWin_.printAt(height_ - SCORE_Y_OFFSET, width_ / WINDOW_WIDTH_DIVISOR - SCORE_X_OFFSET, "Score: %d", score);
    gameWinWin_.wrefresh();
    menuWin_.render();
    
}

GameWinScreen::MenuWindow::MenuWindow(ncui::Window menuWin, GameWinScreen& owner)
    : menuWin_(std::move(menuWin)),
      height_(menuWin_.height()),
      width_(menuWin_.width()),
      owner_(owner)
{}

void GameWinScreen::MenuWindow::render() {
    menuWin_.setKeypad(true);

    int ch;
    while (true) {
        for (int i = 0; i < menuPoints_; ++i) {
            if (i == selectedPoint_)
                menuWin_.attrOn(A_REVERSE);
                menuWin_.printAt(i + 1, 3, "%s", menuItems_[i]);
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
                    owner_.isGameWin_ = true;
                return;
        }
    }
}
