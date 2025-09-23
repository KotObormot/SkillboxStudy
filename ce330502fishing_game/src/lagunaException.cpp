#include "lagunaException.h"

FishException::FishException(const char* message, int attempts) 
        : message(message), attempts(attempts) {}

const char* FishException::what() const noexcept {
      return message;
}

const void FishException::getAttempts() const noexcept {
    std::cout << "Number of attempts: " << attempts << "\n";
}

BootException::BootException(const char* message) : message(message) {}

const char* BootException::what() const noexcept {
    return message;
}

