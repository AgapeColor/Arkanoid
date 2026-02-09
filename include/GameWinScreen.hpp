#pragma once

#include "Window.hpp"

class ConsoleViewport;

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
    bool isGameWin() const noexcept { return isGameWin_; }

private:
    static constexpr int WINDOW_WIDTH_DIVISOR = 2;
    static constexpr double WINDOW_Y_POSITION = 0.3;
    static constexpr double TITLE_Y_POSITION = 0.2;
    static constexpr int TITLE_X_OFFSET = 4;

    static constexpr int MENU_HEIGHT = 5;
    static constexpr int MENU_WIDTH = 14;

    static constexpr int SCORE_Y_OFFSET = 10;
    static constexpr int SCORE_X_OFFSET = 4;

    class MenuWindow {
    public:
        MenuWindow(ncui::Window menuWin, GameWinScreen& owner);
        MenuWindow(const MenuWindow& obj) = delete;
        MenuWindow& operator=(const MenuWindow& obj) = delete;
        MenuWindow(MenuWindow&& obj) = delete;
        MenuWindow& operator=(MenuWindow&& obj) = delete;
        ~MenuWindow() = default;
        
        void render();

    private:
        ncui::Window menuWin_;
        int height_;
        int width_;
        GameWinScreen& owner_;
        const char* menuItems_[2] = {"Restart", "Exit"};
        int menuPoints_ = 2;
        int selectedPoint_ = 0;
    };

    int height_;
    int width_;
    bool isGameWin_;
    ncui::Window gameWinWin_;
    MenuWindow menuWin_;
};
