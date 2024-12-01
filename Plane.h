#pragma once
#include "Cube.h"

class Plane : public Cube
{
public:
    Plane(String name, float width, float height);
    ~Plane();
};
