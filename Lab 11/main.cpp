#include <SFML/Graphics.hpp>
#include "lib/Picture.h"
#include "lib/Line.h"
#include "lib/Rect.h"
#include "lib/Circle.h"
#include "lib/Point.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My C++ Shapes");
    window.setFramerateLimit(60);

    Picture pic;

    pic.addShape(new Line(Point(100, 100), Point(300, 300)));
    pic.addShape(new Rect(Point(400, 100), Point(600, 200)));
    pic.addShape(new Circle(Point(400, 400), 50));

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        pic.draw(window);
        window.display();
    }

    return 0;
}