#pragma once
#include "AUIScreen.h"
class Inspector : public AUIScreen
{
public:
    Inspector();
    ~Inspector();

    // Inherited via AUIScreen
    void drawUI() override;
};

