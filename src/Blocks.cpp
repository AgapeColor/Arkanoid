#include <algorithm>
#include "../include/Blocks.hpp"
#include "../include/GameField.hpp"
#include "../include/Ball.hpp"

Blocks::Blocks(const GameField& field)
    : rows_(field.height() / ROWS_DIVISOR),
      cols_(field.width() - (2 * SIDE_MARGIN)), // Subtract margins from both sides
      blocks_(rows_, std::vector<bool>(cols_, true)),
      destroyedCount_(0)
{}

void Blocks::render(const GameField& field, const Ball& ball) {
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            if (blocks_[row][col] == true) {
                int y = SIDE_MARGIN + row;
                int x = SIDE_MARGIN + col;
                field.fieldWindow().addChAt(y, x, '0');
            }
        }
    }
}

bool Blocks::isBlock(int y, int x) const {
    int row = y - SIDE_MARGIN;
    int col = x - SIDE_MARGIN;

    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        return false;

    return blocks_[row][col];
}

void Blocks::destroyBlock(int y, int x) {
    int row = y - SIDE_MARGIN;
    int col = x - SIDE_MARGIN;
    
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        return;

    if (blocks_[row][col]) {
        blocks_[row][col] = false;
        ++destroyedCount_;
    }
}

void Blocks::reset() {
    for (auto& row : blocks_) {
        std::fill(row.begin(), row.end(), true);
    }
    destroyedCount_ = 0;
}