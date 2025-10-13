#include <iostream>
#include "monitor.h"


Monitor::Monitor(int width, int height): width(width), height(height) {}

Monitor::~Monitor() {}

int Monitor::getWidth() {
    return this->width;
}

int Monitor::getHeight() {
    return this->height;
}

void Monitor::display() {
    for(int i {0}; i < this->height; ++i) {
        for(int j {0}; j < this->width; ++j) {
            if((i >= window.getY() && i < (window.getY() + window.getH()))
                && (j >= window.getX() && j < (window.getX() + window.getW()))) {
                    std::cout << '+';
                } else {
                    std::cout << '.';
                }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Monitor::move() {
    std::cout << "Specify new window coordinates: x";
    int xNew {handlingIntInput()};
    std::cout << "    and y";
    int yNew {handlingIntInput()};
    Window tmpWindow(xNew, yNew, window.getW(), window.getH());
    Window tmpConsole(0, 0, this->width, this->height);
    if(tmpWindow <= tmpConsole) {
        window = tmpWindow;
        std::cout << "New coordinates: x = " << window.getX() << ", y = " << window.getY() << ".\n";
    } else {
        std::cout << "The window doesn't fit.\n";
    }
}

void Monitor::resize() {
    std::cout << "Specify new window proportion: width";
    int widthNew {handlingIntInput()};
    std::cout << "    and height";
    int heightNew {handlingIntInput()};
    Window tmpWindow(window.getX(), window.getY(), widthNew, heightNew);
    Window tmpConsole(0, 0, this->width, this->height);
    if(tmpWindow <= tmpConsole) {
        window = tmpWindow;
        std::cout << "New proportion: width = " << window.getW() << ", height = " << window.getH() << ".\n";
    } else {
        std::cout << "The window doesn't fit.\n";
    }
}