#pragma once

#include <ncurses.h>

namespace ncui {
    using cell_t = chtype;

    namespace acs {
        inline cell_t HLine()    noexcept { return ACS_HLINE; }
        inline cell_t VLine()    noexcept { return ACS_VLINE; }
        inline cell_t ULCorner() noexcept { return ACS_ULCORNER; }
        inline cell_t URCorner() noexcept { return ACS_URCORNER; }
        inline cell_t LLCorner() noexcept { return ACS_LLCORNER; }
        inline cell_t LRCorner() noexcept { return ACS_LRCORNER; }
    }
    namespace key {
        // Arrows
        inline constexpr int Up    = KEY_UP;
        inline constexpr int Down  = KEY_DOWN;
        inline constexpr int Left  = KEY_LEFT;
        inline constexpr int Right = KEY_RIGHT;

        // Letters (lowercase)
        inline constexpr int a = 'a';
        inline constexpr int d = 'd';

        // Letters (uppercase)
        inline constexpr int A = 'A';
        inline constexpr int D = 'D';
    }
}