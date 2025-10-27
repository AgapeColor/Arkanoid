#pragma once

#include "Window.hpp"

class InputHandler {
public:
    explicit InputHandler(const ncui::Window& window) : win_(window) {
        win_.setKeypad(true);
    }
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
    InputHandler(InputHandler&&) = delete;
    InputHandler& operator=(InputHandler&&) = delete;
    ~InputHandler() = default;

    int getInput() const { return win_.getKey(); }
    void setNonBlocking(bool enabled) { win_.setNonBlocking(enabled); }
private:
    const ncui::Window& win_;
};
