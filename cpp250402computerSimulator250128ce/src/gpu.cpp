#include <iostream>
#include "ram.h"
#include "gpu.h"

void gpu_out(RAM gpu) {
    std::cout << "\n---------------------\n";
    std::cout << gpu.i0 << "\t"
              << gpu.i1 << "\t"
              << gpu.i2 << "\t"
              << gpu.i3 << "\t"
              << gpu.i4 << "\t"
              << gpu.i5 << "\t"
              << gpu.i6 << "\t"
              << gpu.i7 << "\n";
    std::cout << "\n**********************\n";
}