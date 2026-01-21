#pragma once

#include <type_traits>
#include <chrono>
#include "NcuiTypes.hpp"

class GameField;
class Platform;

class Ball {
public:
    explicit Ball(const Platform& platform) noexcept;
    Ball(const Ball& obj) = delete;
    Ball& operator=(const Ball& obj) = delete;
    Ball(Ball&& obj) = delete;
    Ball& operator=(Ball&& obj) = delete;
    ~Ball() = default;

    enum class Direction {
        leftUp,
        rightUp,
        leftDown,
        rightDown,
        stop
    };
    
    void setDirection(const GameField& field, const Platform& platform);
    void move();
    void reset(const Platform& platform);
    void render(const GameField& field) const;
    
    // Getters
    bool isBallLost() const noexcept { return isBallLost_; };

private:
// Collision detection block
    enum class Collision {
        none   = 0,
        left   = 1 << 0,
        right  = 1 << 1,
        top    = 1 << 2,
        bottom = 1 << 3
    };
    
    // Overloaded operators for Collision
    friend constexpr Collision operator|(Collision lhs, Collision rhs);
    friend constexpr Collision operator&(Collision lhs, Collision rhs);
    friend Collision operator|=(Collision& lhs, Collision rhs) noexcept;
    friend Collision operator&=(Collision& lhs, Collision rhs) noexcept;

    // Direction info for collision detection
    struct DirectionInfo {
        int yOffset;            // Y offset: -1 (up), +1 (down)
        int xOffset;            // X offset: -1 (left), +1 (right)
        Collision vertical;     // collision type when hitting vertical obstacle
        Collision horizontal;   // collision type when hitting horizontal obstacle
    };
    static constexpr DirectionInfo dirs_[] {
        {-1, -1, Collision::top,    Collision::left},  // leftUp
        {-1,  1, Collision::top,    Collision::right}, // rightUp
        { 1, -1, Collision::bottom, Collision::left},  // leftDown
        { 1,  1, Collision::bottom, Collision::right}  // rightDown
    };
    
    // Main collisions check
    void checkCollisions(const GameField& field, const Platform& platform);

    // Field boundaries collision
    void checkFieldBoundaries(const GameField& field, const DirectionInfo& dir);

    // Platform collision
    void checkPlatformCollision(const Platform& platform, const DirectionInfo& dir);
    void checkPlatformTop(const Platform& platform, const DirectionInfo& dir);
    void checkPlatformWalls(const Platform& platform, const DirectionInfo& dir);

    // Helper methods
    static constexpr bool isCollision(Collision mask, Collision check) noexcept {
        return (mask & check) == check;
    }
    constexpr bool isMovingDown() const noexcept {
        return movement_ == Direction::leftDown || movement_ == Direction::rightDown;
    }
    
    // Data
    static constexpr int ballOffset_ = 1;
    static constexpr int ballLostDistance_ = 2;
    static constexpr int platformEdgeOffset_ = 1; 
    int posY_;
    int posX_;
    bool isMoving_;
    Direction movement_;
    Collision collisionMask_;
    std::chrono::steady_clock::time_point lastMove_;
    std::chrono::milliseconds moveInterval_{75};
    bool isBallLost_;
};

constexpr Ball::Collision operator|(Ball::Collision lhs, Ball::Collision rhs) {
    using U = std::underlying_type_t<Ball::Collision>;
    return static_cast<Ball::Collision>(static_cast<U>(lhs) | static_cast<U>(rhs));
}

constexpr Ball::Collision operator&(Ball::Collision lhs, Ball::Collision rhs) {
    using U = std::underlying_type_t<Ball::Collision>;
    return static_cast<Ball::Collision>(static_cast<U>(lhs) & static_cast<U>(rhs));
}

inline Ball::Collision operator|=(Ball::Collision& lhs, Ball::Collision rhs) noexcept {
    lhs = lhs | rhs;
    return lhs;
}

inline Ball::Collision operator&=(Ball::Collision& lhs, Ball::Collision rhs) noexcept {
    lhs = lhs & rhs;
    return lhs;
}