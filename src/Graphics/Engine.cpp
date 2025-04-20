#include "Engine.h"

#include "GameRender.h"
#include "Viewport.h"
#include "Ui/GameMenu.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

GraphicsEngine::GraphicsEngine(SdlProvider& sdlProvider)
	: window{sdlProvider.GetWindow()}
	, gameUi{std::make_unique<GameMenu>()}
	, gameRender{std::make_unique<GameRender>()}
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
	const auto uiWindowSize = gameUi->GetSize();
	const auto& io = ImGui::GetIO();
	const RectInt drawArea = {int(uiWindowSize.x), 0, int(io.DisplaySize.x), int(io.DisplaySize.y)};
	gameRender->SetDrawArea(drawArea);
}

void GraphicsEngine::Render() {
	const auto& state = gameUi->GetUiState();
	glClearColor(state.clearColor.x, state.clearColor.y, state.clearColor.z, state.clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);

	gameRender->Render();
	gameUi->Render();
}

void GraphicsEngine::PostRender() {
	SDL_GL_SwapWindow(window);
}
