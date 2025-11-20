#pragma once

#include "Window.hpp"

class InputHandler {
public:
    explicit InputHandler(const ncui::Window& window) : win_(window) {
        win_.setKeypad(true);
    }
    InputHandler(const InputHandler& obj) = delete;
    InputHandler& operator=(const InputHandler& obj) = delete;
    InputHandler(InputHandler&& obj) = delete;
    InputHandler& operator=(InputHandler&& obj) = delete;
    ~InputHandler() = default;

    int getInput() const { return win_.getKey(); }
    void setNonBlocking(bool enabled) { win_.setNonBlocking(enabled); }
    void setTimeout(int ms) { win_.setTimeout(ms); }
private:
    const ncui::Window& win_;
};
