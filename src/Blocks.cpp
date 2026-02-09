#include "../include/Blocks.hpp"
#include "../include/GameField.hpp"
#include "../include/Ball.hpp"

Blocks::Blocks(const GameField& field)
    : rows_(field.height() / ROWS_DIVISOR),
      cols_(field.width() - (2 * SIDE_MARGIN)), // Subtract margins from both sides
      blocks_(rows_, std::vector<bool>(cols_, false)),
      destroyedCount_(0),
      generalBlocksAmount_(0)
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

void Blocks::reset() {
    destroyedCount_ = 0;
    generalBlocksAmount_ = 0;
    generateBlocksPattern();
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

void Blocks::generateBlocksPattern() {
        int startRow = rows_ - 1;
        int endRow = 0;
        int startCol = 0;
        int endCol = cols_ - 1;

        for (int row = startRow; row >= endRow; --row) {
            for (int col = startCol; col <= endCol; ++col) {
                if (row == startRow || row  == endRow || col == startCol || col == endCol) {
                    blocks_[row][col] = true;
                    ++generalBlocksAmount_;
                }
            }
            ++startCol;
            --endCol;
        }
}
