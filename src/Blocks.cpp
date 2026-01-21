#include "../include/Blocks.hpp"
#include "../include/GameField.hpp"

Blocks::Blocks(const GameField& field)
    : rows_(field.height() / rowsDivisor_),
      cols_(field.width() - 2 * sideMargin_),
      blocks_(rows_, std::vector<bool>(cols_, true)),
      destroyedCount_(0)
{}

void Blocks::render(const GameField& field) {
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            if (blocks_[row][col] == true) {
                int y = sideMargin_ + row;
                int x = sideMargin_ + col;
                field.fieldWindow().addChAt(y, x, '0');
            }
            else
                field.fieldWindow().addCh(' ');
        }
    }
}