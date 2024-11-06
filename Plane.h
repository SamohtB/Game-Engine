#pragma once
#include "Cube.h"

class Plane : public Cube
{
public:
    Plane();
    ~Plane();

    void initialize() override;
    void update(float deltaTime) override;
};
