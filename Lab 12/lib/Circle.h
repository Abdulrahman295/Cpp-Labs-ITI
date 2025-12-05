#pragma once

#include "GeoShape.h"

class Circle : private GeoShape {
public:
    Circle();
    Circle(float r);

    void setRadius(float r);
    float getRadius();
    float calculateArea();
};
