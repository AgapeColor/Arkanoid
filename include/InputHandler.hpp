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

    // Input operations
    int getInput() const noexcept { return win_.getKey(); }
    void setNonBlocking(bool enabled) const noexcept { win_.setNonBlocking(enabled); }
    void setTimeout(int ms) const noexcept { win_.setTimeout(ms); }

private:
    const ncui::Window& win_;
};
