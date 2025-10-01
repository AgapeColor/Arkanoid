#pragma once

#include <ncurses.h>

class ConsoleViewport;

class SidePanel {
public:
    SidePanel(int height, int width, WINDOW* parent);
    ~SidePanel();
    void render();
    void reset();
    int score() const { return score_; };
    int level() const { return level_; };
private:
    int height_;
    int width_;
    WINDOW* sidePanelWin_;
    int score_;
    int level_;
};
