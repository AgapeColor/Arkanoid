#pragma once

#include <ncurses.h>

class ConsoleViewport;
class SidePanel;

class GameOverScreen {
public:
    GameOverScreen(const ConsoleViewport& viewport, const SidePanel& statistic);
    ~GameOverScreen();
    void render();
    bool isGameOver() const { return isGameOver_; };
private:
    class StatisticWindow {
    public:
        StatisticWindow(int height, int width, WINDOW* parent, const SidePanel& statistic);
        ~StatisticWindow();
        void render();
    private:
        int height_;
        int width_;
        int score_;
        int level_;
        WINDOW* win_;
    };
    class MenuWindow {
    public:
        MenuWindow(int height, int width, WINDOW* parent, GameOverScreen& owner);
        ~MenuWindow();
        void render();
    private:
        int height_;
        int width_;
        WINDOW* win_;
        GameOverScreen& owner_;
    private:
        const char* menuItems_[2] = {"Restart", "Exit"};
        int menuPoints_ = 2;
        int selectedPoint_ = 0;
    };
    int height_;
    int width_;
    bool isGameOver_;
    WINDOW* gameOverWin_;
    StatisticWindow statisticWin_;
    MenuWindow menuWin_;
};