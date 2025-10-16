#pragma once
#include "common.h"
#include "loclib.h"

class Shape {
  protected:    
    Shape() = default;
    ~Shape() = default;
    
    struct BoundingBoxDimensions {                     // dimensions of the circumscribing rectangle;
      double width;
      double height;
    };

    virtual void square() = 0;                        //  returns the area of a figure;
    virtual std::string type() = 0;                     // return the name of a specific type
    virtual BoundingBoxDimensions dimensions() = 0;   // dimensions of the circumscribing rectangle;
    
  public:
    static void printParams(Shape* shape);
};
