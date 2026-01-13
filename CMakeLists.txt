cmake_minimum_required(VERSION 3.10)
project(Arkanoid LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find 'ncurses'
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

# Target
add_executable(arkanoid
    src/main.cpp
    src/GameField.cpp
    src/ConsoleViewport.cpp
    src/Game.cpp
    src/SidePanel.cpp
    src/Platform.cpp
    src/Ball.cpp
    src/GameOverScreen.cpp
    src/GameWindow.cpp
    src/Blocks.cpp
)

# Paths to headers
target_include_directories(arkanoid
  PUBLIC  ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CURSES_INCLUDE_DIRS}
)

# Linking 'ncurses'
target_link_libraries(arkanoid 
    PRIVATE ${CURSES_LIBRARIES}
)