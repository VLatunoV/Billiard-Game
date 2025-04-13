#pragma once
#include <Imgui.h>

struct UiState {
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float circleRad = 57.15f * 1e-3f; // mm
};

class GameMenu {
public:
    void PreRender();
    void Render();

    const UiState& GetUiState() const;
    ImVec2 GetSize() const;

private:
    UiState state;
    ImVec2 windowSize{};
};
