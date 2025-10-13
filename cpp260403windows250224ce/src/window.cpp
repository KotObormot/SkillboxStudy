#include <iostream>
#include "window.h"

Window::Window(int x, int y, int width, int height): x(x), y(y), width(width), height(height) {}

Window::~Window() {}

int Window::getX() {
    return this->x;
}

int Window::getY() {
    return this->y;
}

int Window::getW() {
    return this->width;
}

int Window::getH() {
    return this->height;
}

bool Window::operator <= (const Window& console) {
    return ((this->x >= 0) && (this->y >= 0)                                 /*{true}*/ 
            && ((this->x + this->width) <= console.width)
            && ((this->y + this->height) <= console.height));
}

Window Window::operator = (const Window& window) {
    this->x = window.x;
    this->y = window.y;
    this->width = window.width;
    this->height = window.height;
    return *this;
}