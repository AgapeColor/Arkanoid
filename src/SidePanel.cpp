#include "../include/SidePanel.hpp"
#include "../include/ConsoleViewport.hpp"

SidePanel::SidePanel(int height, int width, WINDOW* parent) 
    : height_(height), 
      width_(width),
      sidePanelWin_(derwin(parent, height_, width_, height, width / 2)),
      score_(0), level_(0)
{}

SidePanel::~SidePanel() {
    delwin(sidePanelWin_);
}

void SidePanel::render() {
    mvwprintw(sidePanelWin_, 1, 1, "Score: %d", score_);
    mvwprintw(sidePanelWin_, 2, 1, "Level: %d", level_);
    wrefresh(sidePanelWin_);
}

void SidePanel::reset() {
    box(sidePanelWin_, 0, 0);
    wrefresh(sidePanelWin_);
    score_ = 0;
    level_ = 0;
}
