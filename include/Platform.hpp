#pragma once

#include <vector>
#include "Window.hpp"
#include "NcuiTypes.hpp"

class GameField;

class Platform {
public:
    enum class Direction {stop, left, right};
    
    Platform(const GameField& field);
    Platform(const Platform&) = delete;
    Platform& operator=(const Platform&) = delete;
    Platform(Platform&&) = delete;
    Platform& operator=(Platform&&) = delete;

    void move(const GameField& field, int dir);
    void render(const GameField& field) const;
    void reset(const GameField& field);
    int posX() const { return posX_; }
    int posY() const { return posY_; }
    int width() const { return width_; }
    Direction movement() const { return movement_; }
private:
    int width_;
    int posY_;
    int posX_;
    std::vector<ncui::cell_t> platform_;
    Direction movement_;
};
