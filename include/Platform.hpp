#pragma once

#include <vector>
#include "Window.hpp"
#include "NcuiTypes.hpp"

class GameField;

class Platform {
public:
    enum class Direction {
        stop,
        left,
        right
    };
    
    Platform(const GameField& field);
    Platform(const Platform& obj) = delete;
    Platform& operator=(const Platform& obj) = delete;
    Platform(Platform&& obj) = delete;
    Platform& operator=(Platform&& obj) = delete;

    void move(const GameField& field, int dir);
    void render(const GameField& field) const;
    void reset(const GameField& field);

    // Getters
    int posX() const noexcept { return posX_; }
    int posY() const noexcept { return posY_; }
    int width() const noexcept { return platformWidth_; }
    Direction movement() const noexcept { return movement_; }
    int centerX() const noexcept { return posX_ + platformWidth_ / 2;}
    int leftEdge() const noexcept { return posX_; }
    int rightEdge() const noexcept { return posX_ + platformWidth_ - 1; }
    
private:
    int platformWidth_;
    int posY_;
    int posX_;
    std::vector<ncui::cell_t> platform_;
    Direction movement_;
};
