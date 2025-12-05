# pragma once

class Point {
private:
    int x, y;
public:
    Point(int xVal, int yVal);
    int getX() const;
    int getY() const;
};