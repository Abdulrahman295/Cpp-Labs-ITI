#pragma once

#include "GeoShape.h"

class Rect : public GeoShape {
public:
    Rect();
    Rect(float x, float y);
    float calculateArea();
};