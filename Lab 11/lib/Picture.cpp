#include "Picture.h"

Picture::~Picture() {
    for (Shape* s : shapes) {
        delete s;
    }
    shapes.clear();
}

void Picture::addShape(Shape* s) {
    shapes.push_back(s);
}

void Picture::draw(sf::RenderWindow& window) const {
    for (const auto& shapePtr : shapes) {
        shapePtr->draw(window);
    }
}