#pragma once
#include "Viewport.h"
#include "Utils/Rect.h"

class GameRender {
public:
    void SetDrawArea(RectInt drawArea);
    void Render();

private:
    void CalculateViewport(RectInt drawArea);

    Viewport viewport;
};
