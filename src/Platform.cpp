#include <algorithm>
#include "../include/Platform.hpp"
#include "../include/GameField.hpp"
#include "../include/NcuiTypes.hpp"

Platform::Platform(const GameField& field)
    : platformWidth_(field.width() / PLATFORM_WIDTH_DIVISOR),
      posY_(field.height() - PLATFORM_Y_OFFSET),
      posX_((field.width() / FIELD_CENTER_DIVISOR) - platformWidth_ / FIELD_CENTER_DIVISOR),
      platform_(platformWidth_, ncui::acs::HLine()),
      movement_(Direction::stop)
{}

void Platform::move(const GameField& field, int dir) {
    switch (dir) {
        case ncui::key::Left:
        case ncui::key::a:
        case ncui::key::A:
            movement_ = Direction::left;
            posX_ = std::max(BORDER_OFFSET, posX_ - MOVE_SPEED);
            break;
            
        case ncui::key::Right:
        case ncui::key::d:
        case ncui::key::D:
            movement_ = Direction::right;
            posX_ = std::min(field.width() - platformWidth_ - BORDER_OFFSET, posX_ + MOVE_SPEED);
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
    platformWidth_ = field.width() / PLATFORM_WIDTH_DIVISOR;
    posY_ = field.height() - PLATFORM_Y_OFFSET;
    posX_ = (field.width() / FIELD_CENTER_DIVISOR) - platformWidth_ / FIELD_CENTER_DIVISOR;
    movement_ = Direction::stop;
}