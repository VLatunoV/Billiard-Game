#pragma once
#include "GameRender.h"
#include "Ui/GameMenu.h"

struct FrameData;

class Scene {
public:
	void PreRender(const FrameData& frameData);
	void Render(const FrameData& frameData);

private:
	GameRender gameRender{};
	GameMenu gameUi{};
};
