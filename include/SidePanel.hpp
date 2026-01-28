#pragma once

#include "Window.hpp"

class ConsoleViewport;

class SidePanel {
public:
    explicit SidePanel(ncui::Window sidePanelWin) noexcept;
    SidePanel(const SidePanel& obj) = delete;
    SidePanel& operator=(const SidePanel& obj) = delete;
    SidePanel(SidePanel&& obj) = delete;
    SidePanel& operator=(SidePanel&& obj) = delete;
    ~SidePanel() = default;
    
    void render();
    void reset();
    void updateScore(int value) { score_ = value; }
    
    // Getters
    int score() const noexcept { return score_; }
    int level() const noexcept { return level_; }
    const ncui::Window& sidePanelWindow() const noexcept { return sidePanelWin_; }

private:
    static constexpr int WINDOW_HEIGHT_DIVISOR = 2;
    static constexpr int WINDOW_WIDTH_DIVISOR = 3;

    ncui::Window sidePanelWin_;
    int height_;
    int width_;
    int score_;
    int level_;
};
