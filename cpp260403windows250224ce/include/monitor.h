#pragma once
#include "window.h"
#include "cci.h"

class Monitor {
  private:
    int width;
    int height;
    Window window{0, 0, 0, 0};
  public:
    Monitor (int, int);
    ~Monitor ();
    int getWidth();
    int getHeight();
    
    void display();
    void move();
    void resize();
};