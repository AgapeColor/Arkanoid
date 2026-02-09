#pragma once

#include "ConsoleViewport.hpp"
#include "GameWindow.hpp"
#include "GameField.hpp"
#include "SidePanel.hpp"
#include "Platform.hpp"
#include "InputHandler.hpp"
#include "Ball.hpp"
#include "GameOverScreen.hpp"
#include "Blocks.hpp"
#include "GameWinScreen.hpp"

class Game {
public:
    Game();
    Game(const Game& obj) = delete;
    Game& operator=(const Game& obj) = delete;
    Game(Game&& obj) = delete;
    Game& operator=(Game&& obj) = delete;
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
    Blocks blocks_;
    GameWinScreen gameWinScreen_;
    bool running_;
    int lastInput_;
    void input();
    void update();
    void render();
    void reset();
};
