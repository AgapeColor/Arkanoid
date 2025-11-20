#include <stdexcept>
#include <algorithm>
#include "../include/ConsoleViewport.hpp"
#include "../include/GameWindow.hpp"
#include "../include/GameField.hpp"
#include "../include/Window.hpp"
#include "../include/NcuiTypes.hpp"

GameField::GameField(ncui::Window fieldWin) 
    : fieldWin_(std::move(fieldWin)),
      height_(fieldWin_.height()),
      width_(fieldWin_.width()),
      field_(height_, std::vector<chtype>(width_, ' ')),
      clearLine(width_ - 2, ' '),
      hasBorders(false)
{
    setFieldBorders();
}

void GameField::render() {
    if (!hasBorders) {
        for (int y = 0; y < height_; ++y) {
            fieldWin_.moveCursor(y, 0);
            fieldWin_.addStr(field_[y].data(), width_);
        }
        hasBorders = true;
    } 
    else {
        for (int y = 1; y < height_ - 1; ++y) {
            fieldWin_.moveCursor(y, 1);
            fieldWin_.addStr(clearLine.data(), width_ - 1);
        }
    }
    fieldWin_.wrefresh();
}

void GameField::reset() {
    for (auto& row : field_)
        std::fill(row.begin(), row.end(), ' ');
    setFieldBorders();
}

ncui::cell_t GameField::cell(int y, int x) const {
    if (y < 0 || y >= height_ || x < 0 || x >= width_)
        throw std::out_of_range("Cell coordinates out of bounds");
    else
        return field_[y][x];
}


void GameField::setFieldBorders() {
    using idx = std::size_t;
    // Init sides of field
    static constexpr idx L = 0, T = 0;
    const idx R = width_ - 1;
    const idx B = height_ - 1;
    // Corners
    field_[T][L] = ncui::acs::ULCorner();
    field_[T][R] = ncui::acs::URCorner();
    field_[B][L] = ncui::acs::LLCorner();
    field_[B][R] = ncui::acs::LRCorner();
    // Top
    std::fill_n(&field_[T][1], width_ - 2, ncui::acs::HLine());
    // Bottom
    std::fill_n(&field_[B][1], width_ - 2, ncui::acs::HLine());
    // Walls
    for (idx y = 1; y < B; ++y) {
        field_[y][L] = ncui::acs::VLine();
        field_[y][R] = ncui::acs::VLine();
    }
    // Borders
    fieldWin_.box();
}