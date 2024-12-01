#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class Hierarchy :  public AUIScreen
{
public:
    Hierarchy();
    ~Hierarchy();


    // Inherited via AUIScreen
    void drawUI() override;

private:
    void drawGameObjectNode(AGameObject* game_object);
};

