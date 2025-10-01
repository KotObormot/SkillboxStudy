#include "array.h"

const unsigned ARRAY_SIZE = 8;

int main() {
    std::cout << "Hello\n";

    Array<double> array(ARRAY_SIZE);
    array.print();
    std::cout << "Arithmetic mean = " << array.arithmeticMean() << "\n";
}
