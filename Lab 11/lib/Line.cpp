#include "Line.h"

Line::Line(Point s, Point e) : start(s), end(e) {}

void Line::draw(sf::RenderWindow& window) const {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(static_cast<float>(start.getX()), static_cast<float>(start.getY()))),
        sf::Vertex(sf::Vector2f(static_cast<float>(end.getX()), static_cast<float>(end.getY())))
    };

    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    window.draw(line, 2, sf::Lines);
}