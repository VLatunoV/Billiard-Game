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

Vector2d Viewport::GetWorldCoordinates(Vector2d screenPoint) const {
	const auto center = (Vector2d(drawArea.x0, drawArea.y0) + Vector2d(drawArea.x1, drawArea.y1)) * 0.5f;
	const auto offset = screenPoint - center;
	const auto xVal = offset.x * (worldWidth / drawArea.Width());
	const auto yVal = offset.y * (worldHeight / drawArea.Height());
	return Vector2d{xVal, -yVal};
}

float Viewport::CalculateWorldScale(int width, int height) const {
	float result = DEFAULT_SCALE;
	result = std::max(result, minWorldWidth / width);
	result = std::max(result, minWorldHeight / height);
	return result;
}
