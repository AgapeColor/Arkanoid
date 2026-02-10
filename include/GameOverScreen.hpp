#pragma once

#include "Window.hpp"
#include "MenuWindow.hpp"

class ConsoleViewport;

class GameOverScreen {
public:
    explicit GameOverScreen(const ConsoleViewport& viewport);
    GameOverScreen(const GameOverScreen& obj) = delete;
    GameOverScreen& operator=(const GameOverScreen& obj) = delete;
    GameOverScreen(GameOverScreen&& obj) = delete;
    GameOverScreen& operator=(GameOverScreen&& obj) = delete;
    ~GameOverScreen() = default;

    void render(int score);

    // Getters
    bool isGameOver() const noexcept { return menuWin_.isRestart(); }

private:
    static constexpr int WINDOW_WIDTH_DIVISOR = 2;
    static constexpr double WINDOW_Y_POSITION = 0.3;
    static constexpr double TITLE_Y_POSITION = 0.2;
    static constexpr int TITLE_X_OFFSET = 5;
    
    static constexpr int MENU_HEIGHT = 5;
    static constexpr int MENU_WIDTH = 14;

    static constexpr int SCORE_Y_OFFSET = 10;
    static constexpr int SCORE_X_OFFSET = 4;

    int height_;
    int width_;
    ncui::Window gameOverWin_;
    MenuWindow menuWin_;
};
