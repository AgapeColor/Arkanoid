#pragma once

#include <ncurses.h>
#include <memory>
#include <stdexcept>

namespace ncui {
    class Window {
    public:
        Window(int height, int width, int beginY, int beginX)
            : win_(::newwin(height, width, beginY, beginX)) {
            if (!win_) throw std::runtime_error("fail of creation new window");
        }

        explicit Window (WINDOW* win) : win_(win) {}

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = default;
        Window& operator=(Window&&) = default;

        Window derwin(int height, int width, int beginY, int beginX) const {
            WINDOW* derived = ::derwin(this->get(), height, width, beginY, beginX);
            if (!derived) throw std::runtime_error("fail of creation derived window");
            return Window(derived);
        }

        explicit operator bool() const { return win_ != nullptr; }

        WINDOW* get() const noexcept { return win_.get(); }

    private:
        struct windowDeleter {
            void operator()(WINDOW* win) const noexcept {
                if (win) delwin(win);
            }
        };
        std::unique_ptr<WINDOW, windowDeleter> win_;
    };
}

