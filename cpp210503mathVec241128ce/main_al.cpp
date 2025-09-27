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

struct Vector {
    double x, y;
};

double length(const Vector& vec) {
    double length;
    length = sqrt(vec.x * vec.x + vec.y * vec.y);
    return length;
}

Vector normalize(Vector& vec) {
    Vector vec1;
    vec1.x = vec.x / length(vec);
    vec1.y = vec.y / length(vec);
    return vec1;
}

Vector add(Vector& vec1, Vector& vec2) {
    Vector vec_sum;
    vec_sum.x = vec1.x + vec2.x;
    vec_sum.y = vec1.y + vec2.y;
    return vec_sum;
}

Vector subtract(Vector& vec1, Vector& vec2) {
    Vector vec_diff;
    vec_diff.x = vec1.x - vec2.x;
    vec_diff.y = vec1.y - vec2.y;
    return vec_diff;
}

Vector scale(Vector& vec, double& f) {
    Vector vec_mult;
    vec_mult.x = vec.x * f;
    vec_mult.y = vec.y * f;
    return vec_mult;
}

void vector_input(Vector& vector, int unary_or_binary_operation_indicator) {
    if(unary_or_binary_operation_indicator == 0) {
        std::cout << "Enter the coordinates of the vector: x";
    } else if(unary_or_binary_operation_indicator == 1) {
        std::cout << "Enter the coordinates of the first vector: x";
    } else {
        std::cout << "Enter the coordinates of the second vector: x";
    }
    vector.x = handling_invalid_input();
    std::cout << " and y";
    vector.y = handling_invalid_input();
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
            Vector vec;
            vector_input(vec, 0);
            double vec_len = length(vec);
            std::cout << "The length of the vector is =" << std::setprecision(2) << vec_len << "\n";
        } else if(choice == 'n' || choice == 'N') {
            Vector vec;
            vector_input(vec, 0);
            Vector v_norm = normalize(vec);
            std::cout << "So, the normalized vector { "
                    << std::setprecision(2) << v_norm.x << ", " << v_norm.y << " }\n"
                    << "Length of a normalized vector = "
                    << length(v_norm) << "\n";

        } else if(choice == '+' || choice == '-') {
            Vector vec;
            vector_input(vec, 1);
            Vector vec2;
            vector_input(vec2, 2);
            if(choice == '+') {
                Vector vec_sum = add(vec, vec2);
                std::cout << "Vector sum { " << std::setprecision(2) 
                          << vec_sum.x << ", " << vec_sum.y << " }\n";
            } else {
                Vector vec_d = subtract(vec, vec2);
                std::cout << "Vector difference { " << std::setprecision(2) 
                          << vec_d.x << ", " << vec_d.y << " }\n";
            }
        } else if(choice == '*') {
            Vector vec;
            vector_input(vec, 0);
            std::cout << "Enter the factor: ";
            double factor = handling_invalid_input();
            Vector vec_mult = scale(vec, factor);
            std::cout << "Vector is the result of multiplication { " << std::setprecision(2)
                      << vec_mult.x << ", " << vec_mult.y << " }\n";
        }
    }    
}