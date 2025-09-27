#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits> // для std::numeric_limits

double handling_invalid_input() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        double x {0};
        std::cin >> x;
        // Проверяем на неудачное извлечение
        if (std::cin.fail()) { // предыдущее извлечение не удалось?        
            // да, давайте разберемся с ошибкой
            std::cin.clear(); // возвращаем нас в "нормальный" режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // и удаляем неверные входные данные
            std::cout << "Oops, that input is invalid.  Please try again: ";
        }   
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; // удаляем любые посторонние входные данные
            return x;
        }
    }   
}

struct Vektor {
    double x, y;
};

double lengh(Vektor& vek) {
    double lenth;
    lenth = sqrt(vek.x * vek.x + vek.y * vek.y);
    return lenth;
}

void normalize(Vektor& vek) {
    Vektor vek1;
    vek1.x = vek.x / lengh(vek);
    vek1.y = vek.y / lengh(vek);
    std::cout << "So, the normalized vector { "
              << std::setprecision(2) << vek1.x << ", " << vek1.y << " }\n"
              << "Length of a normalized vector = "
              << lengh(vek1) << "\n";
}

void add(Vektor& vek1, Vektor& vek2) {
    std::cout << "Vector sum { " << std::setprecision(2) 
              << vek1.x + vek2.x << ", " << vek1.y + vek2.y << " }\n";
}

void subtract(Vektor& vek1, Vektor& vek2) {
    std::cout << "Vector difference { " << std::setprecision(2) 
              << vek1.x - vek2.x << ", " << vek1.y - vek2.y << " }\n";
}

void scale(Vektor& vek, double& f) {
    std::cout << "Vector is the result of multiplication { " << std::setprecision(2)
              << vek.x * f << ", " << vek.y * f << " }\n";
}           

int main() {
    std::cout << "Hello\n";
    std::cout.setf(std::ios::fixed);
    char choice {};
    while(choice != 'q') {
        std::cout << "Enter the operating mode please:\n"
                  << "+ addition of two vectors / "
                  << "- subtraction of two vectors / "
                  << "* vector multiplication by scalar / "
                  << "l Finding the length of a vector / "
                  << "n vector normalization / " 
                  << "q End work"
                  << "--> ";                
        std::cin.clear();        
        std::cin >> choice;
        if(choice == 'l' || choice == 'L') {
            Vektor vek;
            std::cout << "Enter the coordinates of the vector: x";
            vek.x = handling_invalid_input();
            std::cout << " and y";
            vek.y = handling_invalid_input();
            std::cout << "The length of the vector is =" << std::setprecision(2) << lengh(vek) << "\n";
        } else if(choice == 'n' || choice == 'N') {
            Vektor vek;
            std::cout << "Enter the coordinates of the vector: x";
            vek.x = handling_invalid_input();
            std::cout << " and y";
            vek.y = handling_invalid_input();
            normalize(vek);
        } else if(choice == '+' || choice == '-') {
            Vektor vek;
            std::cout << "Enter the coordinates of the first vector: x";
            vek.x = handling_invalid_input();
            std::cout << " and y";
            vek.y = handling_invalid_input();
            Vektor vek2;
            std::cout << "Enter the coordinates of the second vector: x";
            vek2.x = handling_invalid_input();
            std::cout << " and y";
            vek2.y = handling_invalid_input();
            if(choice == '+') {
                add(vek, vek2);
            } else {
                subtract(vek, vek2);
            }
        } else if(choice == '*') {
            Vektor vek;
            std::cout << "Enter the coordinates of the vector: x";
            vek.x = handling_invalid_input();
            std::cout << " and y";
            vek.y = handling_invalid_input();
            std::cout << "Enter the factor: ";
            double factor = handling_invalid_input();
            scale(vek, factor);
        }
    }    
}