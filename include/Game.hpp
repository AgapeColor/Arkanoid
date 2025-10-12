#pragma once

#include "ConsoleViewport.hpp"
#include "GameWindow.hpp"
#include "GameField.hpp"
#include "SidePanel.hpp"
#include "Platform.hpp"
#include "InputHandler.hpp"
#include "Ball.hpp"
#include "GameOverScreen.hpp"

class Game {
public:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
    ~Game() = default;
    
    void run();
private:
    ConsoleViewport viewport_;
    GameWindow gameWindow_;
    GameField& field_;
    SidePanel& sidePanel_;
    Platform platform_;
    Ball ball_;
    InputHandler inputHandler_;
    GameOverScreen gameOverScreen_;
    bool running_;
    int lastInput_;
    void input();
    void update();
    void render();
    void reset();
};
