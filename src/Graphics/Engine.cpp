#include "Engine.h"

#include "FrameData.h"
#include "Scene.h"
#include "Viewport.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

GraphicsEngine::GraphicsEngine(SdlProvider& sdlProvider)
	: window{sdlProvider.GetWindow()}
	, gameScene{std::make_unique<Scene>()}
{

}

GraphicsEngine::~GraphicsEngine() {

}

void GraphicsEngine::DrawFrame() {
	static FrameData frameData;
	PopulateFrameData(frameData);
	PreRender(frameData);
	Render(frameData);
	PostRender(frameData);
}

void GraphicsEngine::PopulateFrameData(FrameData& frameData) {
	auto& io = ImGui::GetIO();
	frameData.io = &io;
	frameData.drawAreaWidth = int(io.DisplaySize.x);
	frameData.drawAreaHeight = int(io.DisplaySize.y);
}

void GraphicsEngine::PreRender(const FrameData& frameData) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	gameScene->PreRender(frameData);
}

void GraphicsEngine::Render(const FrameData& frameData) {
	gameScene->Render(frameData);
}

void GraphicsEngine::PostRender(const FrameData& frameData) {
	SDL_GL_SwapWindow(window);
}
