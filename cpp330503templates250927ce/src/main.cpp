#include "registry.h"
#include "loclib.h"
#include <string>

int main() {

    std::cout << "Hello Erase Vector!\n";

    std::cout << "\n=========== INT ============\n";
    Registry<int> regInt{};
    std::cout << "-------- Add ------------\n";
    regInt.add(67, 69);
    regInt.add(2, 5);
    regInt.add(2, 6);
    regInt.add(2, 7);
    regInt.add(2, 8);
    regInt.add(23, 48);
    regInt.add(2, 9);
    regInt.add(2, 10);
    regInt.add(2, 11);
    regInt.add(3, 10);
    regInt.add(2, 25);

    regInt.print();    
    regInt.find(2);    
    regInt.find(28);
    regInt.remove(2);
    regInt.remove(145);
    regInt.remove(23);
    regInt.print();
    
    std::cout << "\n========== DOUBLE =============\n";
    Registry<double> regDouble{};
    std::cout << "-------- Add ------------\n";
    regDouble.add(3.14, getPI());
    regDouble.add(2.71, getE());
    regDouble.add(22.1, 3.04);
    regDouble.add(22.1, 5.04);
    regDouble.add(48.333, 45.239);
    regDouble.add(22.1, 1186.04);
    regDouble.add(24.255, 1186.04);

    regDouble.find(22.1);
    regDouble.find(48.334);
    regDouble.find(48.333);
    regDouble.print();

    regDouble.remove(2.71);
    regDouble.remove(22.1);
    regDouble.print();

    std::cout << "\n========== STRING =============\n";
    std::cout << "-------- Add ------------\n";
    Registry<std::string> regString{};
    regString.add("Hello", "World");
    regString.add("Goodbye", "Skillbox");
    regString.add("Tom", "Hanks");
    regString.add("Goodbye", "baby");
    regString.add("Tom", "Bombadil");

    regString.print();
    regString.find("Hello");
    regString.find("Thomas");
    regString.remove("Tom");
    regString.remove("Farewell");
    regString.print();
}
