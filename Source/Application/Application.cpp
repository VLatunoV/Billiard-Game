#include "Application.h"

#include "Graphics/Engine.h"
#include "SDL3/SDL.h"
#include "imgui_impl_sdl3.h"

#include <exception>
#include <iostream>

Application::Application() = default;

Application::~Application() = default;

int Application::Run() {
	int result = 0;
	bool startupSuccessful = false;
	try {
		Startup();
		startupSuccessful = true;
		MainLoop();
	}
	catch (std::exception& e) {
		std::cout << "[ERROR]: " << e.what() << std::endl;
		result = -1;
	}
	catch (...) {
		std::cout << "[ERROR]: Unknown error happened" << std::endl;
		result = -2;
	}
	if (startupSuccessful) {
		Shutdown();
	}
	return result;
}

void Application::Startup() {
	sdlModule = std::make_unique<SdlModule>();
	imguiModule = std::make_unique<ImGuiModule>(*sdlModule, *sdlModule);

	graphicsEngine = std::make_unique<GraphicsEngine>(*sdlModule);
}

void Application::Shutdown() {

}

void Application::MainLoop() {
	const auto window = sdlModule->GetWindow();

	state.shouldQuit = false;
	while (state.shouldQuit == false) {
		ProcessEvents();

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
			SDL_Delay(10);
			continue;
		}

		graphicsEngine->DrawFrame();
	}
}

void Application::ProcessEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL3_ProcessEvent(&event);
		if (event.type == SDL_EVENT_QUIT)
			state.shouldQuit = true;
		if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(sdlModule->GetWindow()))
			state.shouldQuit = true;
	}
}
