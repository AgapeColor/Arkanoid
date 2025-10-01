#pragma once

#include <vector>
#include <ncurses.h>

class ConsoleViewport;
class GameWindow;

class GameField {
public:
    GameField(int height, int width, WINDOW* parent, int ownerWidth);
    GameField(const GameField& obj) = delete;
    GameField& operator=(const GameField& obj) = delete;
    GameField(GameField&& obj) = delete;
    GameField& operator=(GameField&& obj) = delete;
    ~GameField();
    void render();
    void reset();
    int height() const { return height_; };
    int width() const { return width_; };
    WINDOW* fieldWin() const { return fieldWin_; };
    chtype cell(int y, int x) const;
private:
    int height_;
    int width_;
    WINDOW* fieldWin_;
    std::vector<std::vector<chtype>> field_;
    const std::vector<chtype> clearLine;
    bool hasBorders;
    void setFieldBorders();   
};
