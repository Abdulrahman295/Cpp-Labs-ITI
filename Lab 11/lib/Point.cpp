#include "Point.h"

Point::Point(int xVal, int yVal) : x(xVal), y(yVal) {}

int Point::getX() const { return x; }

int Point::getY() const { return y; }