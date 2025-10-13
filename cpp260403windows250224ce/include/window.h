#pragma once

class Window {
  private:
    int x;
    int y;
    int width;
    int height;
  public:
    Window(int, int, int, int);    
    ~Window();
    int getX();
    int getY();
    int getW();
    int getH();
    bool operator <= (const Window& console);
    Window operator = (const Window& window);
};
