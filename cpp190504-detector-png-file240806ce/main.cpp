#include <fstream>
#include <iostream>

int main() {
    std::ifstream pngImageFile;
    std::string pathToImage {"../data/png-file.png"};
    std::cout << "Specify the path to the file --> ";
    while(!pngImageFile.is_open()) {
        std::cin >> pathToImage;
        pngImageFile.open(pathToImage, std::iostream::binary);
        if (!pngImageFile.is_open()) {
            std::cerr << "Error opening file! Please type the correct path --> ";
        } else {
            std::cout << "File opened.\n=============================\n";
        }
    }
        
    bool isHeader = false;
    if(!pngImageFile.eof()) {
        int pngHeader[4] {-119, 80, 78, 71} ;
        pngImageFile.seekg(0, std::ios::beg);
        char imageHeader[5] {};
        pngImageFile.get(imageHeader, 5);
        for(int i = 0; i < sizeof(imageHeader) - 1; ++i) {
            isHeader = imageHeader[i] == (int) pngHeader[i] ? true : false;
        }
    }
    if(!isHeader) {
        std::cout << "This file is not png format.\n";
    } else {
        std::string fileExtension {".png"};
        unsigned iExtension = pathToImage.length() - fileExtension.length();
        bool isExtension = (pathToImage.substr(iExtension, fileExtension.length()) == fileExtension) ? true : false;
        
        if(isExtension) {
            std::cout << "This file is in png format.\n";
        } else {
            std::cout << "This file is in png format, but the file extension does not match the png format.\n";
        }
    }

    pngImageFile.close();
    std::cout << "\n=============================\nDetection complete. File closed.\n";
}