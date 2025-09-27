#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
//#include <cstdlib>

int main() {
    std::srand(std::time(nullptr));
    int heightPx, widthPx;
    std::cout << "Enter size of the painting--> ";
    std::cin >> heightPx >> widthPx;

    std::vector<std::vector<char>> pic(heightPx, std::vector<char> (widthPx));
    for(int i = 0; i < heightPx; ++i) {
        for(int j = 0; j < widthPx; ++j) {
            if(std::rand() % 2 == 0) { 
                pic[i][j] = ' ';
            } else {
                pic[i][j] = 'o';
            }
        }
    }

    std::ofstream paint("../data/pic.txt", std::ios::app);
    for(int i = 0; i < heightPx; ++i) {
        for(int j = 0; j < widthPx; ++j) {
            paint << pic[i][j];
        }
        paint << "\n";
    }
    std::cout << "\n";

    paint.close();

}