#pragma once

#include "Rect.h"

class Square : private Rect {
public:
    Square();
    Square(float x);

    void setSquareDim(float x);
    float getSquareDim();
    
    float calculateArea();
};
