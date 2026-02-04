#pragma once

#include <vector>
#include "Window.hpp"
#include "NcuiTypes.hpp"

class ConsoleViewport;

class GameField {
public:
    explicit GameField(ncui::Window fieldWin);
    GameField(const GameField& obj) = delete;
    GameField& operator=(const GameField& obj) = delete;
    GameField(GameField&& obj) = delete;
    GameField& operator=(GameField&& obj) = delete;
    ~GameField() = default;
    
    void render();
    void reset();

    // Getters
    int height() const noexcept { return height_; };
    int width() const noexcept { return width_; };
    const ncui::Window& fieldWindow() const noexcept { return fieldWin_; }
    ncui::cell_t cell(int y, int x) const;
    int leftPlayableX() const noexcept { return 1; }
    int rightPlayableX() const noexcept { return width_ - 1;}
    
private:
    static constexpr int BORDER_WIDTH = 1;
    static constexpr int HORIZONTAL_BORDERS = 2;

    ncui::Window fieldWin_;
    int height_;
    int width_;
    std::vector<std::vector<ncui::cell_t>> field_;
    std::vector<ncui::cell_t> clearLine;
    bool hasBorders;
    void setFieldBorders();
};