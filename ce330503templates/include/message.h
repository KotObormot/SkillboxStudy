#pragma once
#include <iostream>
#include <string>

template<typename T>
struct Message {
    T data;
//    Message(char* indata) : data(indata) {}
    Message(std::string indata) : data(indata) {}
    Message(int indata) : data(indata) {}

    void print() const {
        std::cout << data << "\n";
    }
};
