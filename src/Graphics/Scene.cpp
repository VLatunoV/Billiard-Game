#include "Scene.h"
#include "FrameData.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

void Scene::PreRender(const FrameData& frameData) {
	gameUi.PreRender(frameData);
	const auto uiWindowSize = gameUi.GetSize();
	const RectInt drawArea = {int(uiWindowSize.x), 0, frameData.drawAreaWidth, frameData.drawAreaHeight};
	gameRender.PreRender(drawArea);
}

void Scene::Render(const FrameData& frameData) {
	const auto& state = gameUi.GetUiState();
	glClearColor(state.clearColor.x, state.clearColor.y, state.clearColor.z, state.clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
	gameRender.Render();
	gameUi.Render();
}
