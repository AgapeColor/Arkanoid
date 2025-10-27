#include "../include/Platform.hpp"
#include "../include/GameField.hpp"
#include "NcuiTypes.hpp"

Platform::Platform(const GameField& field)
    : width_(field.width() / 5),
      posY_(field.height() - 3),
      posX_((field.width() / 2) - width_ / 2),
      platform_(width_, ncui::acs::HLine()),
      movement_(Direction::stop)
{}

void Platform::move(const GameField& field, int dir) {
    switch (dir) {
        case ncui::key::Left:
            movement_ = Direction::left;
            if (posX_ > 2) posX_-= 2;
            else if (posX_ > 1) posX_ -= 1;
            break;
        case ncui::key::Right:
            movement_ = Direction::right;
            if (posX_ + width_ < field.width() - 2) posX_ += 2;
            else if (posX_ + width_ < field.width() - 1) posX_ += 1;
            break;
        default:
            movement_ = Direction::stop;
            break;
    }
}

void Platform::render(const GameField& field) const {
    field.fieldWindow().drawHlineAt(posY_, posX_, ncui::acs::HLine(), width_);
}

void Platform::reset(const GameField& field) {
    width_ = field.width() / 5;
    posY_ = field.height() - 3;
    posX_ = (field.width() / 2) - width_ / 2;
    movement_ = Direction::stop;
}
