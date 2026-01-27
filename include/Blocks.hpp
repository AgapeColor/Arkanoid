#pragma once

#include <vector>

class GameField;
class Ball;

class Blocks {
public:
    explicit Blocks(const GameField& field);
    Blocks(const Blocks& obj) = delete;
    Blocks& operator=(const Blocks& obj) = delete;
    Blocks(Blocks&& obg) = delete;
    Blocks& operator=(Blocks&& obj) = delete;
    ~Blocks() = default;

    void reset();

    // Getters
    void render(const GameField& field, const Ball& ball);
    bool isBlock(int y, int x) const;
    void destroyBlock(int y, int x);

private:
    static constexpr int sideMargin_ = 3;
    static constexpr int rowsDivisor_ = 3;

    int rows_;
    int cols_;

    std::vector<std::vector<bool>> blocks_;
    int destroyedCount_;
};

// Changes:
// added isBlock method
// added destroyBlock method