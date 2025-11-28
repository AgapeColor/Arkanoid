#include "../include/Ball.hpp"
#include "GameField.hpp"
#include "Platform.hpp"
#include "NcuiTypes.hpp"

Ball::Ball(const Platform& platform)
    : posY_(platform.posY() - ballOffset_),
      posX_(platform.centerX()),
      isMoving_(false),
      movement_(Direction::stop),
      collisionMask_(Collision::none),
      lastMove_(std::chrono::steady_clock::now()),
      isBallLost_(false)
{}

void Ball::setDirection(const GameField& field, const Platform& platform) {
    // Set the first ball's direction
    if (!isMoving_) {
        isMoving_ = true;
        movement_ = (platform.movement() == Platform::Direction::left) 
            ? Ball::Direction::rightUp
            : (platform.movement() == Platform::Direction::right)
                ? Ball::Direction::leftUp
                : Ball::Direction::stop;
        if (movement_ == Ball::Direction::stop)
            isMoving_ = false;
        return;
    }

    checkCollision(field, platform);
    if (collisionMask_ == Collision::none)
        return;

    if (hasCollision(collisionMask_, Collision::bottom) &&
        posY_ >= field.height() - ballLostDistance_) {
            isBallLost_ = true;
            return;
    }

    auto processBounce = [&](Collision corner, Direction cornerBounce,
                             Collision edge1,  Direction edge1Bounce,
                             Collision edge2,  Direction edge2Bounce) {
        if (hasCollision(collisionMask_, corner))
            movement_ = cornerBounce;
        else if (hasCollision(collisionMask_, edge1))
            movement_ = edge1Bounce;
        else if (hasCollision(collisionMask_, edge2))
            movement_ = edge2Bounce;
    };

    switch (movement_) {
        case Ball::Direction::leftUp:
            processBounce(Collision::top | Collision::left, Direction::rightDown,
                          Collision::top,  Direction::leftDown,
                          Collision::left, Direction::rightUp);
            break;

        case Ball::Direction::rightUp:
            processBounce(Collision::top  | Collision::right, Direction::leftDown,
                          Collision::top,   Direction::rightDown,
                          Collision::right, Direction::leftUp);
            break;

        case Ball::Direction::leftDown:
            processBounce(Collision::bottom | Collision::left, Direction::rightUp,
                          Collision::bottom,  Direction::leftUp,
                          Collision::left,    Direction::rightDown);
            break;

        case Ball::Direction::rightDown:
            processBounce(Collision::bottom | Collision::right, Direction::leftUp,
                          Collision::bottom,  Direction::rightUp,
                          Collision::right,   Direction::leftDown);
            break;

        default:
            break;
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
    posY_ = platform.posY() - ballOffset_;
    posX_ = platform.centerX();
    isMoving_ = false;
    movement_ = Direction::stop;
    collisionMask_= Collision::none;
    lastMove_= std::chrono::steady_clock::now();
    isBallLost_= false;
}

void Ball::checkCollision(const GameField& field, const Platform& platform) {
    collisionMask_ = Collision::none;

    if (movement_ == Direction::stop)
        return;

    const DirectionInfo& dir = dirs_[static_cast<int>(movement_)];

    ncui::cell_t cellVert = field.cell(posY_ + dir.y, posX_);
    ncui::cell_t cellHoriz = field.cell(posY_, posX_ + dir.x);

    if ((movement_ == Ball::Direction::leftDown || movement_ == Ball::Direction::rightDown) &&
        posY_ == field.height() - platformCheckDistance_) {
        checkPlatformCollision(field, platform, posY_ + dir.y, posX_ + dir.x, cellVert, cellHoriz);
    }
    
    if (cellVert != ' ' && cellHoriz == ' ')
        collisionMask_ |= dir.vert;
    else if (cellVert != ' ' && cellHoriz != ' ')
        collisionMask_ |= dir.vert | dir.horiz;
    else if (cellVert == ' ' && cellHoriz != ' ')
        collisionMask_ |= dir.horiz;
}

  void Ball::checkPlatformCollision(const GameField& field, const Platform& platform,
                                    int posY, int posX, ncui::cell_t& cellVert, ncui::cell_t& cellHoriz) {
    if (posY == platform.posY()) {
        if (posX == platform.posX()) {
            cellVert = ncui::acs::HLine();
            if (movement_ == Ball::Direction::rightDown)
                cellHoriz = ncui::acs::VLine();
        }
        else if (posX == platform.posX() + platform.width() - 1) {
            cellVert = ncui::acs::HLine();
            if (movement_ == Ball::Direction::leftDown)
                cellHoriz = ncui::acs::VLine();
        }
        else if (posX > platform.posX() && posX < (platform.posX() + platform.width() - 1))
            cellVert = ncui::acs::HLine();
    }
  }