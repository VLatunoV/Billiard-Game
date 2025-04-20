#include "GameRender.h"

#include "Utils/Vector.h"

#include <imgui.h>
#include <SDL3/SDL_opengl.h>

#include <cmath>
#include <algorithm>

#define PI 3.14159265358979323846f

void DrawCircle(Vector2d center, float radius) {
	const auto length = 2.0f * PI * radius;
	const int numSegments = std::max(16, int(24 * (radius / 0.2f)));

	glBegin(GL_LINE_LOOP);
	for (uint32_t i = 0; i < numSegments; ++i) {
		const float arg = (2.0f*PI*i)/numSegments;
		glVertex2f(center.x + radius*std::cos(arg), center.y + radius*std::sin(arg));
	}
	glEnd();
}

void DrawCoordinateSystem(float left, float right, float bottom, float top) {
	const ImVec4 color{1.0f, 1.0f, 1.0f, 1.0f};
	const auto width = right-left;
	const auto height = top-bottom;
	const auto tickRatio = 0.02f;
	const auto numTicks = 10;

	glBegin(GL_LINES);
	// Horizontal line
	glVertex2f(left, 0.0f);
	glVertex2f(right, 0.0f);

	// Vertical line
	glVertex2f(0.0f, bottom);
	glVertex2f(0.0f, top);

	for (int i = 1, iEnd = std::max(width, height)/2*numTicks; i <= iEnd; ++i) {
		const auto tickLength = tickRatio;
		const float y = float(i)/numTicks;
		// Horizontal line
		glVertex2f(-tickLength, y);
		glVertex2f(tickLength, y);
		glVertex2f(-tickLength, -y);
		glVertex2f(tickLength, -y);

		// Vertical line
		glVertex2f(y, -tickLength);
		glVertex2f(y, tickLength);
		glVertex2f(-y, -tickLength);
		glVertex2f(-y, tickLength);
	}

	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(4, 0x00ff);
	glBegin(GL_LINES);
	for (int i = 1, iEnd = std::max(width, height)/2*numTicks; i <= iEnd; ++i) {
		if (i % 10 != 0) continue;
		const auto tickLength = std::max(width, height);
		const float y = float(i)/numTicks;
		// Horizontal line
		glVertex2f(-tickLength, y);
		glVertex2f(tickLength, y);
		glVertex2f(-tickLength, -y);
		glVertex2f(tickLength, -y);

		// Vertical line
		glVertex2f(y, -tickLength);
		glVertex2f(y, tickLength);
		glVertex2f(-y, -tickLength);
		glVertex2f(-y, tickLength);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void GameRender::SetDrawArea(RectInt drawArea) {
	CalculateViewport(drawArea);
}

void GameRender::Render() {
	viewport.MakeGlViewport();
	const auto halfWidth = viewport.GetWorldWidth() / 2.f;
	const auto halfHeight = viewport.GetWorldHeight() / 2.f;

	DrawCoordinateSystem(-halfWidth, halfWidth, -halfHeight, halfHeight);
	// DrawCircle({0, 0}, state.circleRad);

	const auto& io = ImGui::GetIO();
	const auto p = viewport.GetWorldCoordinates(Vector2d{io.MousePos.x, io.MousePos.y});
	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(p.x, p.y);
	glEnd();
}

void GameRender::CalculateViewport(RectInt drawArea) {
	viewport.SetDrawArea(drawArea);
}
