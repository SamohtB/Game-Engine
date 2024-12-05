#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"
#include "PhysicsComponent.h"

class Inspector : public AUIScreen
{
public:
    Inspector();
    ~Inspector();

    // Inherited via AUIScreen
    void drawUI() override;
    void drawTransformTab(AGameObject* object);
    void drawPhysicsTab(AGameObject* object);
};

