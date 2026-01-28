#include "../include/GameWindow.hpp"
#include "../include/ConsoleViewport.hpp"

GameWindow::GameWindow(const ConsoleViewport& viewport) 
    : height_(viewport.height()),
      width_(viewport.width()),
      gameWin_(height_, width_, 1, 1),  // Position at y = 1, x = 1 (1 - cell offset)
      field_(gameWin_.derwin(height_ - FIELD_BORDER_OFFSET,
                             width_  / FIELD_WIDTH_SCALE,
                             FIELD_Y_OFFSET,
                             width_  / FIELD_X_DIVISOR)),

      sidePanel_(gameWin_.derwin(height_ / PANEL_HEIGHT_DIVISOR,
                                 width_  / PANEL_WIDTH_DIVISOR,
                                 height_ / PANEL_Y_DIVISOR,
                                 width_  / PANEL_X_DIVISOR))
{}

void GameWindow::render() {
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