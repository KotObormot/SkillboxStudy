#pragma once
#include <vector>
#include <iostream>

template<typename T>
class Registry {
  private:
    struct OneRow {
        T key;
        T value;

        OneRow() = default;
        ~OneRow() = default;
        OneRow(T key, T value) : key(key), value(value) {};
        
        void print() const;
    };
    std::vector<OneRow> registry;

  public:
    Registry() = default;
    ~Registry() = default;

    void add(T, T);
    void remove(T);
    void print();
    void find(T);
};

template<typename T>
void Registry<T>::OneRow::print() const {
    std::cout << key << ":\t" << value << "\n";
}

template<typename T>
void Registry<T>::add(T key, T value) {
    OneRow oneRow(key, value);
    registry.emplace_back(oneRow);
}

template<typename T>
void Registry<T>::remove(T keyToRemove) {
    std::cout << "-------- Remove ----------\n";
    int countRemoved(0);
    auto iter{registry.begin()};
    while(iter != registry.end()) {
        if(iter->key == keyToRemove) {
            ++countRemoved;
            registry.erase(iter);
        } else {
            ++iter;
        }
    }

    if(countRemoved) {
        std::cout << keyToRemove << " was successfully deleted.\n";
    } else {
        std::cout << keyToRemove << " not found.\n";
    }
}

template<typename T>
void Registry<T>::find(T keyToFind) {
    std::cout << "----------- Find -----------\n";
    int countFound (0);
    std::vector<OneRow> rows{};

    for(const auto& row : registry) {
        if(row.key == keyToFind) {
            ++countFound;
            rows.emplace_back(row);
        }
    }
    
    if(countFound) {
        std::cout << keyToFind << "  was successfully found.\n";
        for(const auto& row : rows) {
            row.print();
        }
    } else {
        std::cout << keyToFind << " not found.\n";
    }
}

template<typename T>
void Registry<T>::print() {
    std::cout << "-------- Print --------------\n";
    for(const auto& row : registry) {
        row.print();
    }
}
