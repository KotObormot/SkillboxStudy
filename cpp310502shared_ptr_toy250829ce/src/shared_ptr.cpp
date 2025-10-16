
#include "common.h"
#include "shared_ptr.h"

Shared_ptr_toy::Shared_ptr_toy() : ptr(nullptr), counter(nullptr) {}

Shared_ptr_toy::Shared_ptr_toy(Toy* ptr) 
        : ptr(ptr), counter(new size_t(1)) {}

Shared_ptr_toy::Shared_ptr_toy(const std::string& toyName) {
    ptr = new Toy(toyName);
    counter = new size_t(1);
}

Shared_ptr_toy::Shared_ptr_toy(const Shared_ptr_toy& other) 
        : ptr(other.ptr), counter(other.counter) {
    if (counter) {
        ++(*counter);
    }
}

Shared_ptr_toy& Shared_ptr_toy::operator=(const Shared_ptr_toy& other) {
    if(this == &other) {
        return *this;
    }
    
    if (ptr && --(*counter) == 0) {
        delete ptr;
        ptr = nullptr;
        delete counter;
        counter = nullptr;
    }
    
    ptr = other.ptr;
    counter = other.counter;

    if (counter) {
        ++(*counter);
    }

    return *this;
}    

Toy* Shared_ptr_toy::get() const {
    return ptr;
}

void Shared_ptr_toy::reset() {
    if (ptr) {
        --*counter;

        if (*counter == 0) {         
            delete ptr;
            ptr = nullptr;
            delete counter;
            counter = nullptr;
        }
    }
}

size_t Shared_ptr_toy::use_count() const {
    return ptr ? *counter : 0;
}

std::string Shared_ptr_toy::getToyName() {
    return ptr ? ptr->getNmae() : "Nothing";
}

Shared_ptr_toy::~Shared_ptr_toy() {
    if(!counter) {
        return;
    }
    --*counter;
    if(!*counter) {
        delete counter;
        counter = nullptr;
        delete ptr;
        ptr = nullptr;
    }
}

Shared_ptr_toy make_shared_toy(const std::string& toyName) {
    return new Toy(toyName);
}

