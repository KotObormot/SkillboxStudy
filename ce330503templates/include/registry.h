//#include <unordered_map>
#include <vector>
#include <iostream>
#include <iomanip>

template<typename T>
class Registry {
  private:
    struct OneRow {
        T key;
        T value;
        OneRow() = default;
        ~OneRow() = default;
        OneRow(T key, T value) : key(key), value(value) {};
        void print() const {
            std::cout << std::fixed << std::setprecision(2) << key << ":\t" << value << "\n";
        }
    };
    std::vector<OneRow> registry;

  public:
    Registry() = default;
    ~Registry() = default;

    void add(T, T);
    //void remove(T);
    void print();
    //void find();
};

template<typename T>
void Registry<T>::add(T key, T value) {
    OneRow oneRow(key, value);
    registry.emplace_back(oneRow);
}
/*
template<typename T>
void Registry<T>::remove(T key) {
    registry.erase(key);
}
*/ 
template<typename T>
void Registry<T>::print() {
    for(const auto& row : registry) {
        row.print();
    }
    std::cout << "------------------------\n";
}