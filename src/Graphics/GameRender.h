#pragma once
#include "Viewport.h"
#include "Utils/Rect.h"

class GameRender {
public:
    void PreRender(RectInt drawArea);
    void Render();

private:
    void CalculateViewport(RectInt drawArea);

    Viewport viewport;
};
