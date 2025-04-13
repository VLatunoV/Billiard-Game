#pragma once
#include "Utils/Rect.h"

class Viewport {
public:
	void MakeGlViewport();

	void SetDrawArea(RectInt _drawArea);
	void SetMinimumWorldWidth(float width);
	void SetMinimumWorldHeight(float height);

	float GetWorldWidth() const;
	float GetWorldHeight() const;

private:
	float CalculateWorldScale(int width, int height) const;

	RectInt drawArea;
	float scale{};
	float minWorldWidth{};
	float minWorldHeight{};
	float worldWidth{};
	float worldHeight{};
};
