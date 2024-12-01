#pragma once
#include "Cube.h"

class Plane : public Cube
{
public:
    Plane(String name, float width = 1, float height = 1);
    ~Plane();
};
