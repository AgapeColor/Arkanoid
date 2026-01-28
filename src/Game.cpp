#include <chrono>
#include <thread>
#include <iostream>
#include "Game.hpp"

Game::Game()
    : viewport_(),
      gameWindow_(viewport_),
      field_(gameWindow_.gameField()),
      sidePanel_(gameWindow_.sidePanel()),
      platform_(gameWindow_.gameField()),
      ball_(platform_),
      inputHandler_(field_.fieldWindow()),
      gameOverScreen_(viewport_, sidePanel_),
      blocks_(field_),
      running_(true),
      lastInput_(0)
{}

void Game::input() {
    lastInput_ = inputHandler_.getInput();
}

void Game::run() {
    using namespace std::chrono;
    constexpr auto targetFrameDuration = milliseconds(16);
    viewport_.initialize();
    inputHandler_.setNonBlocking(true);
    do {
        running_ = true;
        reset();
        while (running_) {
            auto frameStartTime = steady_clock::now();

            input();
            update();
            render();
            
            auto frameEndTime = steady_clock::now() - frameStartTime;
            if (frameEndTime < targetFrameDuration)
                std::this_thread::sleep_for(targetFrameDuration - frameEndTime);
        }
        gameOverScreen_.render();
    }
    while (!gameOverScreen_.isGameOver());
}

void Game::update() {
    platform_.move(field_, lastInput_);
    ball_.setDirection(field_, platform_, blocks_);
    ball_.move();
    sidePanel_.updateScore(blocks_.destroyedCount());
    if (ball_.isBallLost())
        running_ = false;
}

void Game::render() {
    gameWindow_.render();
    platform_.render(field_);
    blocks_.render(field_, ball_);
    ball_.render(field_);
    field_.fieldWindow().wrefresh();
    sidePanel_.sidePanelWindow().wrefresh();
}

void Game::reset() {
    platform_.reset(field_);
    ball_.reset(platform_);
    blocks_.reset();
    gameWindow_.reset();
}
