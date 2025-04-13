#include "Engine.h"

#include "Viewport.h"
#include "Ui/GameMenu.h"
#include "Utils/Vector.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <type_traits>
#include <cmath>
#include <iostream>

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

GraphicsEngine::GraphicsEngine(SdlProvider& sdlProvider)
	: window{sdlProvider.GetWindow()}
	, gameUi{std::make_unique<GameMenu>()}
{

}

GraphicsEngine::~GraphicsEngine() {

}

void GraphicsEngine::DrawFrame() {
	PreRender();
	Render();
	PostRender();
}

void GraphicsEngine::PreRender() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	gameUi->PreRender();
}

void GraphicsEngine::Render() {
	auto& io = ImGui::GetIO();
	const UiState& state = gameUi->GetUiState();
	const auto windowSize = gameUi->GetSize();
	
	// Rendering
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(state.clearColor.x, state.clearColor.y, state.clearColor.z, state.clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);

	const float scale = 1.0f/240;
	const ImVec4 drawArea{windowSize.x, 0.0f, io.DisplaySize.x - windowSize.x, io.DisplaySize.y};
	const auto worldWidth = scale*(drawArea.z) / 2.0f;
	const auto worldHeight = scale*(drawArea.w) / 2.0f;
	glViewport(int(drawArea.x), int(drawArea.y), int(drawArea.z), int(drawArea.w));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-worldWidth, worldWidth, -worldHeight, worldHeight, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	DrawCoordinateSystem(-worldWidth, worldWidth, -worldHeight, worldHeight);
	DrawCircle({0, 0}, state.circleRad);

	gameUi->Render();
}

void GraphicsEngine::PostRender() {
	SDL_GL_SwapWindow(window);
}
