#pragma once

#include <ncurses.h>
#include "Window.hpp"

class ConsoleViewport;
class SidePanel;

class GameOverScreen {
public:
    GameOverScreen(const ConsoleViewport& viewport, const SidePanel& statistic);
    GameOverScreen(const GameOverScreen& obj) = delete;
    GameOverScreen& operator=(const GameOverScreen& obj) = delete;
    GameOverScreen(GameOverScreen&& obj) = delete;
    GameOverScreen& operator=(GameOverScreen&& obj) = delete;
    ~GameOverScreen() = default;

    void render();
    bool isGameOver() const { return isGameOver_; };
private:
    class StatisticWindow {
    public:
        StatisticWindow(ncui::Window statisticWin, const SidePanel& statistic);
        StatisticWindow(const StatisticWindow& obj) = delete;
        StatisticWindow& operator=(const StatisticWindow& obj) = delete;
        StatisticWindow(StatisticWindow&& obj) noexcept = default;
        StatisticWindow& operator=(StatisticWindow&& obj) = delete;
        ~StatisticWindow() = default;
        void render();
    private:
        ncui::Window statisticWin_;
        int height_;
        int width_;
        int score_;
        int level_;
    };
    class MenuWindow {
    public:
        MenuWindow(ncui::Window menuWin, GameOverScreen& owner);
        MenuWindow(const MenuWindow& obj) = delete;
        MenuWindow& operator=(const MenuWindow& obj) = delete;
        MenuWindow(MenuWindow&& obj) noexcept = default;
        MenuWindow& operator=(MenuWindow&& obj) = delete;
        ~MenuWindow() = default;
        
        void render();
    private:
        ncui::Window menuWin_;
        int height_;
        int width_;
        GameOverScreen& owner_;
    private:
        const char* menuItems_[2] = {"Restart", "Exit"};
        int menuPoints_ = 2;
        int selectedPoint_ = 0;
    };
    int height_;
    int width_;
    bool isGameOver_;
    ncui::Window gameOverWin_;
    StatisticWindow statisticWin_;
    MenuWindow menuWin_;
};