#pragma once

#include <vector>
#include "NcuiTypes.hpp"

class GameField;

class Platform {
public:
    explicit Platform(const GameField& field);
    Platform(const Platform& obj) = delete;
    Platform& operator=(const Platform& obj) = delete;
    Platform(Platform&& obj) = delete;
    Platform& operator=(Platform&& obj) = delete;
    ~Platform() = default;
    
    enum class Direction {
        stop,
        left,
        right
    };
    
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
    static constexpr int PLATFORM_WIDTH_DIVISOR = 5;
    static constexpr int PLATFORM_Y_OFFSET = 3;
    static constexpr int FIELD_CENTER_DIVISOR = 2;
    static constexpr int MOVE_SPEED = 3;
    static constexpr int BORDER_OFFSET = 1;

    int platformWidth_;
    int posY_;
    int posX_;
    std::vector<ncui::cell_t> platform_;
    Direction movement_;
};