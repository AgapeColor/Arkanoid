#pragma once

#include <ncurses.h>
#include "Window.hpp"

class ConsoleViewport;

class SidePanel {
public:
    SidePanel(ncui::Window sidePanelWin);
    SidePanel(const SidePanel& obj) = delete;
    SidePanel& operator=(const SidePanel& obj) = delete;
    SidePanel(SidePanel&& obj) noexcept = default;
    SidePanel& operator=(SidePanel&& obj) = delete;
    ~SidePanel() = default;
    
    void render();
    void reset();
    int score() const { return score_; }
    int level() const { return level_; }
private:
    ncui::Window sidePanelWin_;
    int height_;
    int width_;
    int score_;
    int level_;
};
