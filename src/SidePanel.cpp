#include "../include/SidePanel.hpp"

SidePanel::SidePanel(ncui::Window SidePanelWin) noexcept
    : sidePanelWin_(std::move(SidePanelWin)),
      height_(sidePanelWin_.height()),
      width_(sidePanelWin_.width()),
      score_(0),
      level_(0)
{}

void SidePanel::render() {
    sidePanelWin_.printAt(height_ / WINDOW_HEIGHT_DIVISOR,
                          width_ / WINDOW_WIDTH_DIVISOR,
                          "Score: %d",
                          score_);
    // sidePanelWin_.printAt(2, 1, "Level: %d", level_);
    sidePanelWin_.wrefresh();
}

void SidePanel::reset() {
    sidePanelWin_.box();
    sidePanelWin_.wrefresh();
    score_ = 0;
    level_ = 0;
}
