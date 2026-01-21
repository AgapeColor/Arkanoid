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
            if (!win_)
                throw std::runtime_error("fail of creation new window");
        }
        explicit Window (WINDOW* win) : win_(win) {
            if (!win)
                throw std::invalid_argument("Window pointer is null");
        }
        Window(const Window& obj) = delete;
        Window& operator=(const Window& obj) = delete;
        Window(Window&& obj) = default;
        Window& operator=(Window&& obj) = default;
        ~Window() = default; 

        // Create derived window
        Window derwin(int height, int width, int beginY, int beginX) const {
            WINDOW* derived = ::derwin(this->win_.get(), height, width, beginY, beginX);
            if (!derived)
                throw std::runtime_error("fail of creation derived window");
            return Window(derived);
        }

        // Getters
        explicit operator bool() const noexcept { return win_ != nullptr; }
        int height() const noexcept { return getmaxy(win_.get()); }
        int width() const noexcept { return getmaxx(win_.get()); }

    // Ncurses API wrappers
        // input
        void setKeypad(bool enabled) const {
            if (::keypad(win_.get(), enabled ? TRUE : FALSE) == ERR)
                throw std::runtime_error("keypad() failed");
        }
        void setNonBlocking(bool enabled) const {
            if (::nodelay(win_.get(), enabled ? TRUE : FALSE) == ERR)
                throw std::runtime_error("nodelay() failed");
        }
        void setTimeout(int ms) const noexcept { ::wtimeout(win_.get(), ms); }
        int getKey() const noexcept { return ::wgetch(win_.get()); }

        // render
        void box(chtype vertCh = 0, chtype horizCh = 0) const {
            if (::box(win_.get(), vertCh, horizCh) == ERR)
                throw std::runtime_error("box() failed");
        }
        void wrefresh() const {
            if (::wrefresh(win_.get()) == ERR)
                throw std::runtime_error("wrefresh() failed");
        }
        void wclear() const {
            if (::wclear(win_.get()) == ERR)
                throw std::runtime_error("wclear() failed");
        }
        void moveCursor(int y, int x) const { 
            if(::wmove(win_.get(), y, x) == ERR)
                throw std::runtime_error("wmove() failed");
        }
        
        // char
        void addCh(chtype ch) const {
            if (::waddch(win_.get(), ch) == ERR)
                throw std::runtime_error("waddch() failed");
        }
        void addChAt(int y, int x, chtype ch) const {
            if (mvwaddch(win_.get(), y, x, ch) == ERR)
                throw std::runtime_error("mvwaddch() failed"); 
        }
        
        // string
        void addStr(const chtype* str, int n) const {
            if (::waddchnstr(win_.get(), str, n) == ERR)
                throw std::runtime_error("waddchnstr() failed");
        }
        void addStrAt(int y, int x, const chtype* str, int n) const {
            if (mvwaddchnstr(win_.get(), y, x, str, n) == ERR)
                throw std::runtime_error("mvwaddchnstr() failed");
        }
        
        // formatted string
        template <typename... Args>
        void print(const char* str, Args&&... args) const {
            ::wprintw(win_.get(), str, std::forward<Args>(args)...);
        }
        template <typename... Args>
        void printAt(int y, int x, const char* str, Args&&... args) const {
            if constexpr (sizeof...(Args) == 0)
                (::wmove(win_.get(), y, x) == ERR) ? ERR : ::waddstr(win_.get(), str);
            else
                ::mvwprintw(win_.get(), y, x, str, std::forward<Args>(args)...);
        }
                
        // horizontal line
        void drawHline(chtype ch, int n) const {
            if (::whline(win_.get(), ch, n) == ERR)
                throw std::runtime_error("whline() failed");
        }
        void drawHlineAt(int y, int x, chtype ch, int n) const {
            if (mvwhline(win_.get(), y, x, ch, n) == ERR)
                throw std::runtime_error("mvwhline() failed");
        }
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

