#include "Rect.h"

Rect::Rect() : GeoShape() {}

Rect::Rect(float x, float y) : GeoShape(x, y) {}

float Rect::calculateArea() {
    return dim1 * dim2;
}