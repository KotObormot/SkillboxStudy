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
    int remover(T);

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
    bool isRmvd(remover(keyToRemove));
    if(isRmvd) {
        std::cout << keyToRemove << " was successfully deleted.\n";
    } else {
        std::cout << keyToRemove << " not found.\n";
    }
}

template<typename T>
int Registry<T>::remover(T keyToRemove) {
    int countRemoved(0);
    for(auto iter{registry.begin()}; iter != (registry.end() - 1); ++iter) {
        if(iter->key == keyToRemove) {
            ++countRemoved;
            registry.erase(iter);
        } 
        else { 
            break; 
        }        
        remover(keyToRemove);
    }
 
    if(registry.end()->key == keyToRemove) {
        ++countRemoved;
        registry.pop_back();
    }
    return countRemoved;
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
