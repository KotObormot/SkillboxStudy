#pragma once
#include <iostream>

template<typename T>
class Array {
  private:
    unsigned size;
    T* data;
  public:
    Array(unsigned);
    ~Array();

    T arithmeticMean() const;
    void print() const;
};

template<typename T>
Array<T>::Array(unsigned size) : size(size) {
    this->data = new T[size];
    std::cout << "Fill the array [" << size << "]-->";
    for(unsigned i(0); i < size; ++i) {
        std::cin >> data[i];
    }
}

template<typename T>
Array<T>::~Array() {
    delete[] data;
}

template<typename T>
void Array<T>::print() const {
    for(unsigned i(0); i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

template<typename T>
T Array<T>::arithmeticMean() const {
    T sum(0);
    for(unsigned i(0); i < size; ++i) {
        sum += data[i];
    }
    return sum / size;
}

