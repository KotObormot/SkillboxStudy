#include <iostream>
#include <cpu.h>
#include <ram.h>

void compute(RAM cpu) {
    int sum = cpu.i0 + cpu.i1 + cpu.i2 + cpu.i3 + cpu.i4 + cpu.i5 + cpu.i6 + cpu.i7;
    std::cout << "Result = " << sum << "\n";
}