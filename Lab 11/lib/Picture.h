#include <vector>
#include <SFML/Graphics.hpp>
#include "Shape.h"

class Picture {
private:
    std::vector<Shape*> shapes; // edit to be pointer to pointers array of shape.
public:
    ~Picture();

    void addShape(Shape* s);

    void draw(sf::RenderWindow& window) const;
};
