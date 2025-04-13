#include "Viewport.h"

#include <SDL3/SDL_opengl.h>

#include <algorithm>

// 240 pixels = 1 meter
constexpr float DEFAULT_SCALE = 1.0f / 240.0f;

void Viewport::MakeGlViewport() {
	const auto drawAreaWidth = drawArea.Width();
	const auto drawAreaHeight = drawArea.Height();
	glViewport(drawArea.x0, drawArea.y0, drawAreaWidth, drawAreaHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Viewport::SetDrawArea(RectInt _drawArea) {
	drawArea = _drawArea;
	const auto drawAreaWidth = drawArea.Width();
	const auto drawAreaHeight = drawArea.Height();
	scale = CalculateWorldScale(drawAreaWidth, drawAreaHeight);
	worldWidth = scale * drawAreaWidth;
	worldHeight = scale * drawAreaHeight;
}

void Viewport::SetMinimumWorldWidth(float width) {
	minWorldWidth = width;
}

void Viewport::SetMinimumWorldHeight(float height) {
	minWorldHeight = height;
}

float Viewport::GetWorldWidth() const {
	return worldWidth;
}

float Viewport::GetWorldHeight() const {
	return worldHeight;
}

float Viewport::CalculateWorldScale(int width, int height) const {
	float result = 1.0 / 240.f;
	if (minWorldWidth > 0.0f) result = std::min(result, minWorldWidth / width);
	if (minWorldHeight > 0.0f) result = std::min(result, minWorldHeight / height);
	return result;
}
