    #pragma once

    #include "Window.hpp"

    class MenuWindow {
    public:
        MenuWindow(ncui::Window menuWin);
        MenuWindow(const MenuWindow& obj) = delete;
        MenuWindow& operator=(const MenuWindow& obj) = delete;
        MenuWindow(MenuWindow&& obj) = delete;
        MenuWindow& operator=(MenuWindow&& obj) = delete;
        ~MenuWindow() = default;
        
        enum class Choice { Restart, Exit };

        void render();
        
        // Getters
        bool isRestart() const noexcept { return isRestart_; }

    private:       
        ncui::Window menuWin_;
        int height_;
        int width_;
        const char* menuItems_[2] = {"Restart", "Exit"};
        int menuPoints_ = 2;
        int selectedPoint_ = 0;
        bool isRestart_;
    };