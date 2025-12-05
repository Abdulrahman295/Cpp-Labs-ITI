#pragma once

#include "GeoShape.h"

class Triangle : public GeoShape {
public:
    Triangle(); 
    Triangle(float b, float h);
    float calculateArea();
};
