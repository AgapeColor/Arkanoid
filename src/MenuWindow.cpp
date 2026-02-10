#include "../include/MenuWindow.hpp"

MenuWindow::MenuWindow(ncui::Window menuWin)
    : menuWin_(std::move(menuWin)),
      height_(menuWin_.height()),
      width_(menuWin_.width())
{}

void MenuWindow::render() {
    menuWin_.setKeypad(true);

    int ch;
    while (true) {
        for (int i = 0; i < menuPoints_; ++i) {
            if (i == selectedPoint_)
                menuWin_.attrOn(A_REVERSE);
                menuWin_.printAt(i + 1, 3, "%s", menuItems_[i]);
            menuWin_.attrOff(A_REVERSE);
        }
        menuWin_.wrefresh();

        ch = menuWin_.getKey();
        switch (ch) {
            case KEY_UP:
                selectedPoint_ = (selectedPoint_ - 1 + menuPoints_) % menuPoints_;
                break;
            case KEY_DOWN:
                selectedPoint_ = (selectedPoint_ + 1) % menuPoints_;
                break;
            case '\n':
                if (selectedPoint_ == 1)
                    isRestart_ = true;
                return;
        }
    }
}