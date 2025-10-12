#pragma once

class ConsoleViewport {
public:
    ConsoleViewport(int marginY = 1, int marginX = 1);
    ConsoleViewport(const ConsoleViewport& obj) = delete;
    ConsoleViewport& operator=(const ConsoleViewport& obj) = delete;
    ConsoleViewport(ConsoleViewport&& obj) = delete;
    ConsoleViewport& operator=(ConsoleViewport&& obj) = delete;
    ~ConsoleViewport();
    
    void initialize() const;
    int height() const { return rows_; }
    int width() const { return cols_; }
private:
    int rows_, cols_;
    int marginY_, marginX_;
    void detectWindowSize();
};
