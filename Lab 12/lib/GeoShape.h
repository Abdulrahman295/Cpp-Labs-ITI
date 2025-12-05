#pragma once

class GeoShape {
protected:
    float dim1;
    float dim2;

public:
    GeoShape();
    GeoShape(float x);
    GeoShape(float x, float y);

    void setDim1(float x);
    void setDim2(float x);

    float getDim1();
    float getDim2();

    float calculateArea();
};
