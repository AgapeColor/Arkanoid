#include "../include/Blocks.hpp"
#include "../include/GameField.hpp"

Blocks::Blocks(const GameField& field)
    : rows_(field.height() / 3),
      cols_(field.width() - 2 * sideMargin_),
      blocks_(rows_ * cols_),
      destroyedCount_(0)
{
    generateBlocks(field);
}

void Blocks::render(const GameField& field) {
    for (const auto& el : blocks_)
        field.fieldWindow().addChAt(el.y, el.x, '0');
}

void Blocks::generateBlocks(const GameField& field) {
    int startPosY = 3;
    int startPosX = 3;
    for (int i = 0, j = 1; i < blocks_.size(); ++i, ++j) {
        blocks_[i].y = startPosY;
        blocks_[i].x = startPosX++;
        if (j / cols_ == 1) {
            ++startPosY;
            startPosX = 3;
            j = 0;
        }
        blocks_[i].isDestroyed = false;
    }
}