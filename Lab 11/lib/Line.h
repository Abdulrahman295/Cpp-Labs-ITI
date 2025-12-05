#pragma once

#include "Shape.h"
#include "Point.h"

class Line : public Shape {
private:
    Point start, end;
public:
    Line(Point s, Point e);
    void draw(sf::RenderWindow& window) const override;
};