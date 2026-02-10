#pragma once

#include "Window.hpp"
#include "MenuWindow.hpp"

class ConsoleViewport;
class MenuWindow;

class GameWinScreen {
public:
    explicit GameWinScreen(const ConsoleViewport& viewport);
    GameWinScreen(const GameWinScreen& obj) = delete;
    GameWinScreen& operator=(const GameWinScreen& obj) = delete;
    GameWinScreen(GameWinScreen&& obj) = delete;
    GameWinScreen& operator=(GameWinScreen&& obj) = delete;
    ~GameWinScreen() = default;

    void render(int score);

    // Getters
    bool isGameWin() const noexcept { return menuWin_.isRestart(); }

private:
    static constexpr int WINDOW_WIDTH_DIVISOR = 2;
    static constexpr double WINDOW_Y_POSITION = 0.3;
    static constexpr double TITLE_Y_POSITION = 0.2;
    static constexpr int TITLE_X_OFFSET = 4;

    static constexpr int MENU_HEIGHT = 5;
    static constexpr int MENU_WIDTH = 14;

    static constexpr int SCORE_Y_OFFSET = 10;
    static constexpr int SCORE_X_OFFSET = 4;

    int height_;
    int width_;
    ncui::Window gameWinWin_;
    MenuWindow menuWin_;
};
