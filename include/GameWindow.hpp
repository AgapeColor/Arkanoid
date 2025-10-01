#pragma once

#include <ncurses.h>
#include "../include/SidePanel.hpp"
#include "../include/GameField.hpp"

class ConsoleViewport;

class GameWindow {
public:
    GameWindow(const ConsoleViewport& viewport);
    GameWindow(const GameWindow& obj) = delete;
    GameWindow& operator=(const GameWindow& obj) = delete;
    GameWindow(GameWindow&& obj) = delete;
    GameWindow& operator=(GameWindow&& obj) = delete;
    ~GameWindow();
    
    void render();
    void reset();
    int height() const { return height_; }
    int width() const { return width_; }
    WINDOW* gameWindow() const { return gameWin_; }
    GameField& gameField() { return field_; }
    SidePanel& sidePanel() { return sidePanel_; }
private:
    int height_;
    int width_;
    WINDOW* gameWin_;
    SidePanel sidePanel_;
    GameField field_;
};