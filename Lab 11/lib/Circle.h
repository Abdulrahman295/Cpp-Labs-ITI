# pragma once

#include "Shape.h"
#include "Point.h"

class Circle : public Shape {
private:
    Point cen;
    int r;
public:
    Circle(Point c, int radius);
    void draw(sf::RenderWindow& window) const override;
};
