#pragma once

struct RAM {
    int i0;
    int i1;
    int i2;
    int i3;
    int i4;
    int i5;
    int i6;
    int i7;    
};

RAM write(RAM);

RAM read(RAM);
