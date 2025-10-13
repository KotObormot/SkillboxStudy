#include "ram.h"

RAM write(RAM in) {
    RAM ram {};
    ram.i0 = in.i0;
    ram.i1 = in.i1;
    ram.i2 = in.i2;
    ram.i3 = in.i3;
    ram.i4 = in.i4;
    ram.i5 = in.i5;
    ram.i6 = in.i6;
    ram.i7 = in.i7;
    return ram;
}

RAM read(RAM ram) {
    RAM out {};
    out.i0 = ram.i0;
    out.i1 = ram.i1;
    out.i2 = ram.i2;
    out.i3 = ram.i3;
    out.i4 = ram.i4;
    out.i5 = ram.i5;
    out.i6 = ram.i6;
    out.i7 = ram.i7;
    return out;
}
