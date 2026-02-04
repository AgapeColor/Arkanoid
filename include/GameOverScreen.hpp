#pragma once

#include "Window.hpp"

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
    bool isGameOver() const noexcept { return isGameOver_; }

private:
    class StatisticWindow {
    public:
        StatisticWindow(ncui::Window statisticWin);
        StatisticWindow(const StatisticWindow& obj) = delete;
        StatisticWindow& operator=(const StatisticWindow& obj) = delete;
        StatisticWindow(StatisticWindow&& obj) = delete;
        StatisticWindow& operator=(StatisticWindow&& obj) = delete;
        ~StatisticWindow() = default;

        void render(int score);
        
    private:
        ncui::Window statisticWin_;
        int height_;
        int width_;
    };

    class MenuWindow {
    public:
        MenuWindow(ncui::Window menuWin, GameOverScreen& owner);
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
        GameOverScreen& owner_;
        const char* menuItems_[2] = {"Restart", "Exit"};
        int menuPoints_ = 2;
        int selectedPoint_ = 0;
    };
    
    static constexpr int WINDOW_HEIGHT_DIVISOR = 2;
    static constexpr int WINDOW_WIDTH_DIVISOR = 2;
    static constexpr int WINDOW_WIDTH_INDENT = 2;
    static constexpr double WINDOW_Y_POSITION = 0.3;
    static constexpr double TITLE_Y_POSITION = 0.2;
    static constexpr int TITLE_X_OFFSET = 5;

    int height_;
    int width_;
    bool isGameOver_;
    ncui::Window gameOverWin_;
    StatisticWindow statisticWin_;
    MenuWindow menuWin_;
};
