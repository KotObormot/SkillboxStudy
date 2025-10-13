#include <fstream>
#include "disk.h"
#include "ram.h"

void save(RAM disk) {
    std::ofstream file("../data/data.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    file.write((char*)& disk, sizeof(disk));
    file.close();
}

RAM load() {
    RAM disk {};
    std::ifstream file("../data/data.bin", std::ios::in | std::ios::binary);
    if(file.is_open()) {
        file.read((char*)& disk, sizeof(disk));
        file.close();
    }
    return disk;
}