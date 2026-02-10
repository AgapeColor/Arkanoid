#include "../include/GameOverScreen.hpp"
#include "../include/ConsoleViewport.hpp"


GameOverScreen::GameOverScreen(const ConsoleViewport& viewport)
    : height_(viewport.height()),
      width_(viewport.width()),
      gameOverWin_(height_, width_, 1, 1),  // Position at y = 1, x = 1 (1 - cell offset)
      menuWin_(gameOverWin_.derwin(MENU_HEIGHT, MENU_WIDTH,
                                   height_ * WINDOW_Y_POSITION,
                                   width_  / WINDOW_WIDTH_DIVISOR - (MENU_WIDTH / WINDOW_WIDTH_DIVISOR)))
{}

void GameOverScreen::render(int score) {
    gameOverWin_.wclear();
    gameOverWin_.box();
    gameOverWin_.printAt(height_ * TITLE_Y_POSITION, width_ / WINDOW_WIDTH_DIVISOR - TITLE_X_OFFSET, "Game Over");
    gameOverWin_.printAt(height_ - SCORE_Y_OFFSET, width_ / WINDOW_WIDTH_DIVISOR - SCORE_X_OFFSET, "Score: %d", score);
    gameOverWin_.wrefresh();
    menuWin_.render();
}

