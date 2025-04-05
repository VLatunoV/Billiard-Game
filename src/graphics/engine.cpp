#include "engine.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"



#include <type_traits>
#include "physics/vector.h"
#include <cmath>
#include <iostream>
using namespace math;

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
{

}

GraphicsEngine::~GraphicsEngine() {

}

void GraphicsEngine::DrawFrame() {
	DrawFrameInternal();
	SDL_GL_SwapWindow(window);
}

void GraphicsEngine::DrawFrameInternal() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();
	auto& io = ImGui::GetIO();

	// Our state
	static bool show_demo_window = false;
	static bool show_another_window = false;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	static float circleRad = 57.15f * 1e-3f; // mm

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	const char windowName[] = "Testing window";
	static float f = 0.0f;
	static int counter = 0;

	ImGui::SetNextWindowPos(ImVec2{0.0f, 0.0f});
	ImGui::SetNextWindowCollapsed(false);
	ImGui::SetNextWindowSize(ImVec2{0, io.DisplaySize.y});
	ImGui::Begin(windowName, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);                          // Create a window called "Hello, world!" and append into it.
	const auto windowSize = ImGui::GetWindowSize();

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &show_another_window);

	ImGui::SliderFloat("Radius", &circleRad, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	// 3. Show another simple window.
	if (show_another_window) {
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	ImGui::GetForegroundDrawList()->AddText(ImVec2{io.MousePos.x, -10 + io.MousePos.y}, ImColor(255.0f, 0.0f, 0.0f, 255.0f), "My text");

	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
	DrawCircle({0, 0}, circleRad);
}
