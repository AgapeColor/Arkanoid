#include <iostream>
#include "Game.hpp"

Game::Game()
    : viewport_(),
      gameWindow_(viewport_),
      field_(gameWindow_.gameField()),
      sidePanel_(gameWindow_.sidePanel()),
      platform_(gameWindow_.gameField()),
      ball_(platform_),
      inputHandler_(field_.fieldWin()),
      gameOverScreen_(viewport_, sidePanel_),
      running_(true)
{}

void Game::input() {
    lastInput_ = inputHandler_.getInput();
}

void Game::run() {
    viewport_.initialize();
    inputHandler_.setNonBlocking(true);
    do {
        running_ = true;
        reset();
        while (running_) {
            input();
            update();
            render();
        }
        gameOverScreen_.render();
    }
    while (!gameOverScreen_.isGameOver());
}

void Game::update() {
    platform_.move(field_, lastInput_);
    ball_.setDirection(field_, platform_);
    ball_.move();
    if (ball_.isBallLost())
        running_ = false;
}

void Game::render() {
    gameWindow_.render();
    // sidePanel_.render();
    // field_.render();
    platform_.render(field_);
    ball_.render(field_);
}

void Game::reset() {
    platform_.reset(field_);
    ball_.reset(platform_);
    gameWindow_.reset();
}
