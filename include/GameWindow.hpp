#pragma once

#include <ncurses.h>
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
    int height() const { return height_; }
    int width() const { return width_; }
    WINDOW* gameWindow() const { return gameWin_.get(); }
    GameField& gameField() { return field_; }
    SidePanel& sidePanel() { return sidePanel_; }
private:
    int height_;
    int width_;
    ncui::Window gameWin_;
    SidePanel sidePanel_;
    GameField field_;
};