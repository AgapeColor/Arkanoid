#pragma once

#include <vector>
#include <ncurses.h>
#include "Window.hpp"

class ConsoleViewport;

class GameField {
public:
    GameField(ncui::Window fieldWin);
    GameField(const GameField& obj) = delete;
    GameField& operator=(const GameField& obj) = delete;
    GameField(GameField&& obj) noexcept = default;
    GameField& operator=(GameField&& obj) = default;
    ~GameField() = default;
    
    void render();
    void reset();
    int height() const { return height_; };
    int width() const { return width_; };
    WINDOW* fieldWin() const noexcept { return fieldWin_.get(); }
    const ncui::Window& fieldWindow() const noexcept { return fieldWin_; }
    chtype cell(int y, int x) const;
private:
    ncui::Window fieldWin_;
    int height_;
    int width_;
    std::vector<std::vector<chtype>> field_;
    std::vector<chtype> clearLine;
    bool hasBorders;
    void setFieldBorders();
};
