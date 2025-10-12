#include "../include/SidePanel.hpp"
#include "../include/ConsoleViewport.hpp"

SidePanel::SidePanel(ncui::Window SidePanelWin)
    : sidePanelWin_(std::move(SidePanelWin)),
      height_(sidePanelWin_.height()),
      width_(sidePanelWin_.width()),
      score_(0), level_(0)
{}

void SidePanel::render() {
    mvwprintw(sidePanelWin_.get(), 1, 1, "Score: %d", score_);
    mvwprintw(sidePanelWin_.get(), 2, 1, "Level: %d", level_);
    wrefresh(sidePanelWin_.get());
}

void SidePanel::reset() {
    box(sidePanelWin_.get(), 0, 0);
    wrefresh(sidePanelWin_.get());
    score_ = 0;
    level_ = 0;
}
