#include "Circle.h"

Circle::Circle(Point c, int radius) : cen(c), r(radius) {}

void Circle::draw(sf::RenderWindow& window) const {
    sf::CircleShape circle(static_cast<float>(r));

    circle.setPosition(
        static_cast<float>(cen.getX() - r),
        static_cast<float>(cen.getY() - r)
    );

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1.0f);

    window.draw(circle);
}