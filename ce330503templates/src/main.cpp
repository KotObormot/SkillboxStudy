#include "message.h"
#include "registry.h"
#include "loclib.h"
#include <iomanip>

int main() {
/*
    std::cout << "double";
    double d = handlingInput<double>(14.3);
    std::cout << std::fixed << std::setprecision(4) << d << "\n";

    std::cout << "int";
    int j = handlingInput(14.3);
    std::cout << std::fixed << std::setprecision(2) << j << "\n";


    std::cout << std::fixed << std::setprecision(5) << getPI() << "\n";

    Message<std::string> m("Hello!");    
    m.print();

    Message<int> i(42);
    i.print();
    */

    
    Registry<int> regInt{};
    regInt.add(2, 5);
    regInt.add(2, 6);
    regInt.add(3, 10);
    std::cout << "=======================\n";
    regInt.print();
    /*regInt.remove(2);
    regInt.print();*/

    Registry<double> regDouble{};
    regDouble.add(2.71, 3.14);
    regDouble.add(18.23111, 13.15);
    regDouble.add(22.1, 3.04);
    regDouble.print();

    Registry<std::string> regString{};
    regString.add("Hello", "World");
    regString.print();
}
