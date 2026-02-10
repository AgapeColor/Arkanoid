#include "../include/GameWinScreen.hpp"
#include "../include/ConsoleViewport.hpp"


GameWinScreen::GameWinScreen(const ConsoleViewport& viewport)
    : height_(viewport.height()),
      width_(viewport.width()),
      gameWinWin_(height_, width_, 1, 1),  // Position at y = 1, x = 1 (1 - cell offset)
      menuWin_(gameWinWin_.derwin(MENU_HEIGHT, MENU_WIDTH,
                                  height_ * WINDOW_Y_POSITION,
                                  width_ / WINDOW_WIDTH_DIVISOR - (MENU_WIDTH / WINDOW_WIDTH_DIVISOR)))
{}

void GameWinScreen::render(int score) {
    gameWinWin_.wclear();
    gameWinWin_.box();
    gameWinWin_.printAt(height_ * TITLE_Y_POSITION, width_ / WINDOW_WIDTH_DIVISOR - TITLE_X_OFFSET, "You win!");
    gameWinWin_.printAt(height_ - SCORE_Y_OFFSET, width_ / WINDOW_WIDTH_DIVISOR - SCORE_X_OFFSET, "Score: %d", score);
    gameWinWin_.wrefresh();
    menuWin_.render();
}
