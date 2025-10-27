#pragma once

#include <ncurses.h>
#include <memory>
#include <stdexcept>
#include <utility>

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
            WINDOW* derived = ::derwin(this->win_.get(), height, width, beginY, beginX);
            if (!derived) throw std::runtime_error("fail of creation derived window");
            return Window(derived);
        }
        explicit operator bool() const { return win_ != nullptr; }
        int height() const { return getmaxy(win_.get()); }
        int width() const { return getmaxx(win_.get()); }
    // ncurses API wrappers
        // input
        void setKeypad(bool enabled) const noexcept { ::keypad(win_.get(), enabled ? TRUE : FALSE); }
        void setNonBlocking(bool enabled) const noexcept { ::nodelay(win_.get(), enabled ? TRUE : FALSE); }
        int getKey() const noexcept { return ::wgetch(win_.get()); }
        // render
        void box(chtype verch = 0, chtype horch = 0) const noexcept { ::box(win_.get(), verch, horch); }
        void wrefresh() const noexcept { ::wrefresh(win_.get()); }
        void wclear() const noexcept { ::wclear(win_.get()); }
        void moveCursor(int y, int x) const noexcept { ::wmove(win_.get(), y, x); }
            // char
        void addCh(chtype ch) const noexcept { ::waddch(win_.get(), ch); }
        void addChAt(int y, int x, chtype ch) const noexcept { mvwaddch(win_.get(), y, x, ch); }
            // string
        void addStr(const chtype* str, int n) const noexcept { ::waddchnstr(win_.get(), str, n); }
        void addStrAt(int y, int x, const chtype* str, int n) const noexcept {
            mvwaddchnstr(win_.get(), y, x, str, n);
        }
            // formatted string
        template <typename... Args>
        void print(const char* str, Args&&... args) const noexcept {
            ::wprintw(win_.get(), str, std::forward<Args>(args)...);
        }
        template <typename... Args>
        void printAt(int y, int x, const char* str, Args&&... args) const noexcept {
            if constexpr (sizeof...(Args) == 0)
                (::wmove(win_.get(), y, x) == ERR) ? ERR : ::waddstr(win_.get(), str);
            else
                ::mvwprintw(win_.get(), y, x, str, std::forward<Args>(args)...);
        }
            // horizontal line
        void drawHline(chtype ch, int n) const noexcept { whline(win_.get(), ch, n); }
        void drawHlineAt(int y, int x, chtype ch, int n) const noexcept { mvwhline(win_.get(), y, x, ch, n); }
            // attributes
        void attrOn(chtype attr) const noexcept { ::wattron(win_.get(), attr); }
        void attrOff(chtype attr) const noexcept { ::wattroff(win_.get(), attr); }
    private:
        struct windowDeleter {
            void operator()(WINDOW* win) const noexcept {
                if (win) delwin(win);
            }
        };
        std::unique_ptr<WINDOW, windowDeleter> win_;
    };
}

