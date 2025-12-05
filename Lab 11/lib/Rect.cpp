#include "Rect.h"

Rect::Rect(Point u, Point l) : ul(u), lr(l) {}

void Rect::draw(sf::RenderWindow& window) const {
    float width = static_cast<float>(lr.getX() - ul.getX());
    float height = static_cast<float>(lr.getY() - ul.getY());

    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(static_cast<float>(ul.getX()), static_cast<float>(ul.getY()));

    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(1.0f);

    window.draw(rect);
}