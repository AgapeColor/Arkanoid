#include "../include/Ball.hpp"
#include "GameField.hpp"
#include "Platform.hpp"
#include "NcuiTypes.hpp"

Ball::Ball(const Platform& platform)
    : posY_(platform.posY() - 1),
      posX_(platform.posX() + (platform.width() / 2)),
      isMoving_(false),
      movement_(Direction::stop),
      collisionMask_(Collision::none),
      lastMove_(std::chrono::steady_clock::now()),
      isBallLost_(false),
      gen_(std::random_device{}())
{}

void Ball::setDirection(const GameField& field, const Platform& platform) {
// Set the first ball's direction
    if (!isMoving_) {
        isMoving_ = true;
        switch (platform.movement()) {
            case Platform::Direction::left:
                movement_ = Ball::Direction::rightUp;
                break;
            case Platform::Direction::right:
                movement_ = Ball::Direction::leftUp;
                break;
            default:
                movement_ = Ball::Direction::stop;
                isMoving_ = false;
            break;
        }
    }
    else {
        switch (movement_) {
        case Ball::Direction::leftUp:
            checkCollision(field, platform);
            if (collisionMask_ == Ball::Collision::none)
                break;
            else {
                if (hasCollision(collisionMask_, Collision::top))
                    movement_ = Ball::Direction::leftDown;
                else if (hasCollision(collisionMask_, Collision::left))
                    movement_ = Ball::Direction::rightUp;
                else if (hasCollision(collisionMask_, Collision::top, Collision::left))
                    movement_ = Ball::Direction::rightDown;
            }
            break;

        case Ball::Direction::rightUp:
            checkCollision(field, platform);
            if (collisionMask_ == Ball::Collision::none)
                break;
            else {
                if (hasCollision(collisionMask_, Collision::top))
                    movement_ = Ball::Direction::rightDown;
                else if (hasCollision(collisionMask_, Collision::right))
                    movement_ = Ball::Direction::leftUp;
                else if (hasCollision(collisionMask_, Collision::top, Collision::right))
                    movement_ = Ball::Direction::leftDown;
            }
            break;

        case Ball::Direction::leftDown:
            checkCollision(field, platform);
            if (collisionMask_ == Ball::Collision::none)
                break;
            else {
                if (hasCollision(collisionMask_, Collision::bottom)) {
                    if (posY_ == field.height() - 2)
                        isBallLost_ = true;
                    else
                        movement_ = Ball::Direction::leftUp;
            }
                else if (hasCollision(collisionMask_, Collision::left))
                    movement_ = Ball::Direction::rightDown;
                else if (hasCollision(collisionMask_, Collision::bottom, Collision::left)) {
                    if (posY_ == field.height() - 2)
                        isBallLost_ = true;
                    else
                        movement_ = Ball::Direction::rightUp;
                }
            }
            break;

        case Ball::Direction::rightDown:
            checkCollision(field, platform);
            if (collisionMask_ == Ball::Collision::none)
                break;
            else {
                if (hasCollision(collisionMask_, Collision::bottom)) {
                    if (posY_ == field.height() - 2)
                        isBallLost_ = true;
                    else
                        movement_ = Ball::Direction::rightUp;
                }
                else if (hasCollision(collisionMask_, Collision::right))
                    movement_ = Ball::Direction::leftDown;
                else if (hasCollision(collisionMask_, Collision::bottom, Collision::right)) {
                    if (posY_ == field.height() - 2)
                        isBallLost_ = true;
                    else
                        movement_ = Ball::Direction::leftUp;
                }
            }
            break;

        default:
            break;
        }
    }
}

void Ball::move() {
    auto now = std::chrono::steady_clock::now();
    if (now - lastMove_ < moveInterval_)
        return;
    lastMove_ = now;
    switch (movement_) {
        case Ball::Direction::leftUp:
            --posY_;
            --posX_;
            break;
        case Ball::Direction::rightUp:
            --posY_;
            ++posX_;
            break;
        case Ball::Direction::leftDown:
            ++posY_;
            --posX_;
            break;
        case Ball::Direction::rightDown:
            ++posY_;
            ++posX_;
            break;  
        default:
            break;
    }
}

void Ball::render(const GameField& field) const {
    field.fieldWindow().addChAt(posY_, posX_, 'O');
}

void Ball::reset(const Platform& platform) {
    posY_= platform.posY() - 1;
    posX_= platform.posX() + platform.width() / 2;
    isMoving_= false;
    movement_ = Direction::stop;
    collisionMask_= Collision::none;
    lastMove_= std::chrono::steady_clock::now();
    isBallLost_= false;
}

void Ball::checkCollision(const GameField& field, const Platform& platform) {
    collisionMask_ = Collision::none;

    if (movement_ == Direction::stop)
        return;

    int currentDir = static_cast<int>(movement_);
    const DirectionInfo& dir = dirs_[currentDir];

    ncui::cell_t cellVert = field.cell(posY_ + dir.y, posX_);
    ncui::cell_t cellHoriz = field.cell(posY_, posX_ + dir.x);

    if ((movement_ == Ball::Direction::leftDown || movement_ == Ball::Direction::rightDown) && posY_ == field.height() - 4)
        checkPlatformCollision(field, platform, posY_ + dir.y, posX_ + dir.x, cellVert, cellHoriz);

    if (cellVert != ' ' && cellHoriz == ' ')
        collisionMask_ |= dir.vert;
    else if (cellVert != ' ' && cellHoriz != ' ')
        collisionMask_ |= dir.vert | dir.horiz;
    else if (cellVert == ' ' && cellHoriz != ' ')
        collisionMask_ |= dir.horiz;
}

  void Ball::checkPlatformCollision(const GameField& field, const Platform& platform,
                                    int posY, int posX, ncui::cell_t& cellVert, ncui::cell_t& cellHoriz) {
    int cornerBounce = dis_(gen_);
    if (posY == platform.posY()) {
        if (posX == platform.posX()) {
            cellVert = ncui::acs::HLine();
            if (movement_ == Ball::Direction::rightDown && cornerBounce == 1)
                cellHoriz = ncui::acs::VLine();
        }
        else if (posX == platform.posX() + platform.width() - 1) {
            cellVert = ncui::acs::HLine();
            if (movement_ == Ball::Direction::leftDown && cornerBounce == 1)
                cellHoriz = ncui::acs::VLine();
        }
        else if (posX > platform.posX() && posX < (platform.posX() + platform.width() - 1))
            cellVert = ncui::acs::HLine();
    }
  }