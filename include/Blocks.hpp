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

    void render(const GameField& field, const Ball& ball);
    void reset();
    bool isAllBlocksDestroyed() const noexcept { return destroyedCount_ == generalBlocksAmount_; }

    // Getters
    bool isBlock(int y, int x) const;
    void destroyBlock(int y, int x);
    int destroyedCount() const noexcept { return destroyedCount_; }

private:
    static constexpr int SIDE_MARGIN = 3;
    static constexpr int ROWS_DIVISOR = 3;

    int rows_;
    int cols_;

    std::vector<std::vector<bool>> blocks_;
    int destroyedCount_;
    int generalBlocksAmount_;
    void generateBlocksPattern();
};
