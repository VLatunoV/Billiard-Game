#pragma once
#include "Viewport.h"
#include "Utils/Rect.h"

class GameRender {
public:
    void PreRender(struct ImVec2 gameMenuSize);
    void Render();

private:
    void CalculateViewport(RectInt drawArea);

    Viewport viewport;
};
