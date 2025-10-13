#pragma once
#include <iostream>
#include <iomanip>
#include "cci.h"

class Shape {
  protected:
    enum class Color {
      START,
      RED = 1,
      WHITE = 2,
      BLACK = 4,
      GREEN = 8,
      END,
    };

    enum class Figure {
      CIRCLE,
      RECTANGLE,
      SQUARE,
      TRIANGLE,
    };

    Color color;
    int x;
    int y;

    virtual void shapeArea() = 0;
    void setXY();    
    std::string getColor (const Color&);
    void printColor();
    void setColor();
    std::string getFigure(const Figure&);
    void printArea(const double&, const double&, const Figure&);
    void setFigure();

  public:    
    Shape();
    ~Shape();
};