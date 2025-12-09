#include "../include/Ball.hpp"
#include "GameField.hpp"
#include "Platform.hpp"
#include "NcuiTypes.hpp"

Ball::Ball(const Platform& platform) noexcept
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
            ? Direction::rightUp
            : (platform.movement() == Platform::Direction::right)
                ? Direction::leftUp
                : Direction::stop;

        if (movement_ == Direction::stop)
            isMoving_ = false;
        return;
    }

    checkCollisions(field, platform);
    if (collisionMask_ == Collision::none)
        return;

    if (isCollision(collisionMask_, Collision::bottom) &&
        posY_ >= field.height() - ballLostDistance_) {
            isBallLost_ = true;
            return;
    }

    auto processBounce = [&](Collision corner, Direction cornerBounce,
                             Collision edge1,  Direction edge1Bounce,
                             Collision edge2,  Direction edge2Bounce) {
        if (isCollision(collisionMask_, corner))
            movement_ = cornerBounce;
        else if (isCollision(collisionMask_, edge1))
            movement_ = edge1Bounce;
        else if (isCollision(collisionMask_, edge2))
            movement_ = edge2Bounce;
    };

    switch (movement_) {
        case Direction::leftUp:
            processBounce(Collision::top | Collision::left, Direction::rightDown,
                          Collision::top,  Direction::leftDown,
                          Collision::left, Direction::rightUp);
            break;

        case Direction::rightUp:
            processBounce(Collision::top  | Collision::right, Direction::leftDown,
                          Collision::top,   Direction::rightDown,
                          Collision::right, Direction::leftUp);
            break;

        case Direction::leftDown:
            processBounce(Collision::bottom | Collision::left, Direction::rightUp,
                          Collision::bottom,  Direction::leftUp,
                          Collision::left,    Direction::rightDown);
            break;

        case Direction::rightDown:
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
        case Direction::leftUp:
            --posY_;
            --posX_;
            break;
        case Direction::rightUp:
            --posY_;
            ++posX_;
            break;
        case Direction::leftDown:
            ++posY_;
            --posX_;
            break;
        case Direction::rightDown:
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
    collisionMask_ = Collision::none;
    lastMove_ = std::chrono::steady_clock::now();
    isBallLost_ = false;
}

void Ball::checkCollisions(const GameField& field, const Platform& platform) {
    collisionMask_ = Collision::none;

    if (movement_ == Direction::stop)
        return;

    const DirectionInfo& dir = dirs_[static_cast<int>(movement_)];

    checkPlatformCollision(platform, dir);
    checkFieldBoundaries(field, dir);
}

void Ball::checkPlatformCollision(const Platform& platform, const DirectionInfo& dir) {
    if (!isMovingDown()) return;

    checkPlatformTop(platform, dir);
    checkPlatformWalls(platform, dir);
}

void Ball::checkFieldBoundaries(const GameField& field, const DirectionInfo& dir) {
    ncui::cell_t cellVert = field.cell(posY_ + dir.yOffset, posX_);
    ncui::cell_t cellHoriz = field.cell(posY_, posX_ + dir.xOffset);

    if (cellVert != ' ' && cellHoriz == ' ')
        collisionMask_ |= dir.vertical;
    else if (cellVert != ' ' && cellHoriz != ' ')
        collisionMask_ |= dir.vertical | dir.horizontal;
    else if (cellVert == ' ' && cellHoriz != ' ')
        collisionMask_ |= dir.horizontal;
}

void Ball::checkPlatformTop(const Platform& platform, const DirectionInfo& dir) {
    int nextBallPosY = posY_ + dir.yOffset;
    int nextBallPosX = posX_ + dir.xOffset;

    if (nextBallPosY != platform.posY()) return;

    if (nextBallPosX == platform.leftEdge()) {
        collisionMask_ |= dir.vertical;
        if (movement_ == Ball::Direction::rightDown)
            collisionMask_ |= dir.horizontal;
    }
    else if (nextBallPosX == platform.rightEdge()) {
        collisionMask_ |= dir.vertical;
        if (movement_ == Ball::Direction::leftDown)
            collisionMask_ |= dir.horizontal;
    }
    else if (nextBallPosX > platform.leftEdge() && nextBallPosX < platform.rightEdge())
        collisionMask_ |= dir.vertical;
}

void Ball::checkPlatformWalls(const Platform& platform, const DirectionInfo& dir) {
     if (posY_ != platform.posY()) return;
        
     if ((posX_ == platform.leftEdge() - platformEdgeOffset_ && movement_ == Direction::rightDown) ||
        (posX_ == platform.rightEdge() + platformEdgeOffset_ && movement_ == Direction::leftDown))
        collisionMask_ |= dir.horizontal;
}