#pragma once
#include <vector>
#include <iostream>

template<typename Key, typename Value>
class Registry {
  private:
    struct OneRow {
        Key key;
        Value value;

        OneRow() = default;
        ~OneRow() = default;
        OneRow(Key key, Value value) : key(key), value(value) {};
        
        void print() const;
    };
    std::vector<OneRow> registry;

  public:
    Registry() = default;
    ~Registry() = default;

    void add(Key, Value);
    void remove(Key);
    void print() const;
    void find(Key) const;
};

template<typename Key, typename Value>
void Registry<Key, Value>::OneRow::print() const {
    std::cout << key << ":\t" << value << "\n";
}

template<typename Key, typename Value>
void Registry<Key, Value>::add(Key key, Value value) {
    OneRow oneRow(key, value);
    registry.emplace_back(oneRow);
}

template<typename Key, typename Value>
void Registry<Key, Value>::remove(Key keyToRemove) {
    std::cout << "-------- Remove ----------\n";
    int countRemoved(0);
    auto iter{registry.begin()};
    while(iter != registry.end()) {
        if(iter->key == keyToRemove) {
            ++countRemoved;
            iter = registry.erase(iter);        // Important! Update the iterator
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

template<typename Key, typename Value>
void Registry<Key, Value>::find(Key keyToFind) const {
    std::cout << "----------- Find -----------\n";

    bool found = false;
    for (const auto& row : registry) {
        if (row.key == keyToFind) {
            if (!found) {
                std::cout << keyToFind << "  was successfully found.\n";
                found = true;
            }
            row.print();
        }
    }
    if (!found) {
        std::cout << keyToFind << " not found.\n";
    }
}

template<typename Key, typename Value>
void Registry<Key, Value>::print() const {
    std::cout << "-------- Print --------------\n";
    for(const auto& row : registry) {
        row.print();
    }
}
