#pragma once
#include "common.h"

class FishException : public std::exception {
  private:
    const char* message;
    int attempts;

  public:
    FishException(const char*, int);
    ~FishException() = default;
    
    const char* what() const noexcept override;
//    const void getAttempts() const noexcept;    // не возвращает значение, а печатает
//                                                // Это нарушает ожидания от геттера — геттер должен возвращать значение, а не печатать.
    const int getAttempts() const noexcept;
};

class BootException : public std::exception {
  private:
    const char* message;

  public:
    BootException(const char*);
    ~BootException() = default;

    const char* what() const noexcept override;
};