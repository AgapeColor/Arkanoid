#pragma once

#include <type_traits>
#include <chrono>
#include <thread>
#include <random>
#include "NcuiTypes.hpp"

class GameField;
class Platform;

class Ball {
public:
    enum class Direction {
        leftUp,
        rightUp,
        leftDown,
        rightDown,
        stop
    };
    
    Ball(const Platform& platform);
    Ball(const Ball&) = delete;
    Ball& operator=(const Ball&) = delete;
    Ball(Ball&&) = delete;
    Ball& operator=(Ball&&) = delete;
    ~Ball() = default;
    
    void setDirection(const GameField& field, const Platform& platform);
    void move();
    void reset(const Platform& platform);
    void render(const GameField& field) const;
    bool isBallLost() const { return isBallLost_; };
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

    // Detection collisions
    struct DirectionInfo {
        int y, x;
        Collision vert, horiz;
    };
    static constexpr DirectionInfo dirs[] {
        {-1, -1, Collision::top,    Collision::left},  // leftUp
        {-1,  1, Collision::top,    Collision::right}, // rightUp
        { 1, -1, Collision::bottom, Collision::left},  // leftDown
        { 1,  1, Collision::bottom, Collision::right}  // rightDown
    };
    
    // Methods for checking collisions
    void checkCollision(const GameField& field, const Platform& platform);
    template <typename ... Args>
    static constexpr bool hasCollision(Collision mask, Args ... args) noexcept {
        static_assert((std::is_same_v<Args, Collision> && ...), "hasCollision: args must be Ball::Collision");
        const Collision combined = (Collision::none | ... | args);
        return mask == combined;
    }
    void checkPlatformCollision(const GameField& field, const Platform& platform, int posY, int posX, ncui::cell_t& cellVert, ncui::cell_t& cellHoriz);
    int posY_;
    int posX_;
    bool isMoving_;
    Direction movement_;
    Collision collisionMask_;
    std::chrono::steady_clock::time_point lastMove_;
    std::chrono::milliseconds moveInterval_{75};
    bool isBallLost_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> dis_{0, 1};
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