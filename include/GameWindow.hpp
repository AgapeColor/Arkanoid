#pragma once

#include "../include/SidePanel.hpp"
#include "../include/GameField.hpp"
#include "Window.hpp"

class ConsoleViewport;

class GameWindow {
public:
    GameWindow(const ConsoleViewport& viewport);
    GameWindow(const GameWindow& obj) = delete;
    GameWindow& operator=(const GameWindow& obj) = delete;
    GameWindow(GameWindow&& obj) = delete;
    GameWindow& operator=(GameWindow&& obj) = delete;
    ~GameWindow() = default;
    
    void render();
    void reset();

    // Getters
    int height() const noexcept { return height_; }
    int width() const noexcept { return width_; }
    GameField& gameField() noexcept { return field_; }
    SidePanel& sidePanel() noexcept { return sidePanel_; }
    
private:
    int height_;
    int width_;
    ncui::Window gameWin_;
    SidePanel sidePanel_;
    GameField field_;
};