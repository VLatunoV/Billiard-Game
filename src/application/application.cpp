#include "application.h"

#include "graphics/engine.h"
#include "SDL3/SDL.h"
#include "imgui_impl_sdl3.h"

#include <exception>
#include <iostream>

Application::Application() = default;

Application::~Application() = default;

int Application::run() {
	int result = 0;
	bool startupSuccessful = false;
	try {
		startup();
		startupSuccessful = true;
		mainLoop();
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
		shutdown();
	}
	return result;
}

void Application::startup() {
	sdlModule = std::make_unique<SdlModule>();
	imguiModule = std::make_unique<ImGuiModule>(*sdlModule.get(), *sdlModule.get());

	graphicsEngine = std::make_unique<GraphicsEngine>(state);
}

void Application::shutdown() {

}

void Application::mainLoop() {
	const auto window = sdlModule->getWindow();

	state.shouldQuit = false;
	while (state.shouldQuit == false) {
		processEvents();

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
			SDL_Delay(10);
			continue;
		}

		graphicsEngine->drawFrame();

		SDL_GL_SwapWindow(window);
	}
}

void Application::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL3_ProcessEvent(&event);
		if (event.type == SDL_EVENT_QUIT)
			state.shouldQuit = true;
		if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(sdlModule->getWindow()))
			state.shouldQuit = true;
	}
}
