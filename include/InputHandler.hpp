#pragma once

#include <ncurses.h>

class InputHandler {
public:
    explicit InputHandler(WINDOW* window) : win_(window) {
        keypad(win_, TRUE);
    }
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
    InputHandler(InputHandler&&) = delete;
    InputHandler& operator=(InputHandler&&) = delete;
    ~InputHandler() = default;

    int getInput() const { return wgetch(win_); }
    void setNonBlocking(bool enabled) { nodelay(win_, enabled ? TRUE : FALSE); }
private:
    WINDOW* win_;
};
