#include <algorithm>
#include "../include/Platform.hpp"
#include "../include/GameField.hpp"
#include "NcuiTypes.hpp"

Platform::Platform(const GameField& field)
    : platformWidth_(field.width() / 5),
      posY_(field.height() - 3),
      posX_((field.width() / 2) - platformWidth_ / 2),
      platform_(platformWidth_, ncui::acs::HLine()),
      movement_(Direction::stop)
{}

void Platform::move(const GameField& field, int dir) {
    constexpr int speed = 3;

    switch (dir) {
        case ncui::key::Left:
        case ncui::key::a:
        case ncui::key::A:
            movement_ = Direction::left;
            posX_ = std::max(1, posX_ - speed);
            break;
            
        case ncui::key::Right:
        case ncui::key::d:
        case ncui::key::D:
            movement_ = Direction::right;
            posX_ = std::min(field.width() - platformWidth_ - 1, posX_ + speed);
            break;

        default:
            movement_ = Direction::stop;
            break;
    }
}

void Platform::render(const GameField& field) const {
    field.fieldWindow().drawHlineAt(posY_, posX_, ncui::acs::HLine(), platformWidth_);
}

void Platform::reset(const GameField& field) {
    platformWidth_ = field.width() / 5;
    posY_ = field.height() - 3;
    posX_ = (field.width() / 2) - platformWidth_ / 2;
    movement_ = Direction::stop;
}
