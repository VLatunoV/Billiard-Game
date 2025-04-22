#pragma once

struct FrameData {
    int drawAreaWidth{};
    int drawAreaHeight{};

    struct ImGuiIO* io{};
};
