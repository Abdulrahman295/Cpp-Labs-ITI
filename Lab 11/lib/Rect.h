# pragma once

#include "Shape.h"
#include "Point.h"

class Rect : public Shape {
private:
    Point ul, lr;
public:
    Rect(Point u, Point l);
    void draw(sf::RenderWindow& window) const override;
};