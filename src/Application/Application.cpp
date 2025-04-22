#include "Application.h"

#include "Game/ObjectManager.h"
#include "Game/Logic.h"
#include "Graphics/Engine.h"
#include "Modules/Imgui.h"
#include "Modules/Sdl.h"

#include <SDL3/SDL.h>
#include <imgui_impl_sdl3.h>

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

	ObservedObjects observed{static_cast<MouseObserved*>(this), static_cast<KeyboardObserved*>(this)};
	objectManager = std::make_unique<ObjectManager>(observed);

	gameLogic = std::make_unique<GameLogic>();
	objectManager->RegisterObject(*gameLogic->GetBoard());

	RegisterObservers();
}

void Application::Shutdown() {}

void Application::MainLoop() {
	const auto window = sdlModule->GetWindow();

	shouldQuit = false;
	while (shouldQuit == false) {
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
		switch (event.type) {
			case SDL_EVENT_QUIT:
				shouldQuit = true;
				break;
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
				if (event.window.windowID == SDL_GetWindowID(sdlModule->GetWindow()))
					shouldQuit = true;
				break;
		}

		HandleInputEvents(event);
	}
}

void Application::HandleInputEvents(SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
		shouldQuit = true;

	const auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse == false) {
		switch (event.type) {
			case SDL_EVENT_MOUSE_BUTTON_DOWN: return Notify(&MouseObserver::MouseDown, event.button);
			case SDL_EVENT_MOUSE_BUTTON_UP: return Notify(&MouseObserver::MouseUp, event.button);
			case SDL_EVENT_MOUSE_MOTION: return Notify(&MouseObserver::MouseMove, event.motion);
		}
	}
	if (io.WantCaptureKeyboard == false) {
		switch (event.type) {
			case SDL_EVENT_KEY_DOWN: return Notify(&KeyboardObserver::KeyDown, event.key);
			case SDL_EVENT_KEY_UP: return Notify(&KeyboardObserver::KeyUp, event.key);
		}
	}
}

void Application::RegisterMouseObserver(MouseObserver* o) {
	MouseObserved::RegisterObserver(o);
}

void Application::RegisterKeyboardObserver(KeyboardObserver* o) {
	KeyboardObserved::RegisterObserver(o);
}

void Application::RegisterObservers() {
	RegisterMouseObserver(this);
	RegisterKeyboardObserver(this);
}

void Application::MouseDown(const SDL_MouseButtonEvent& e) {
	const bool isDoubleClick = (e.clicks == 2);
	std::cout << "Mouse pressed: " << int(e.button) << ", " << int(e.clicks) << ", (" << e.x << ", " << e.y << ")" << std::endl;
}

void Application::MouseUp(const SDL_MouseButtonEvent& e) {
	std::cout << "Mouse released: " << int(e.button) << ", (" << e.x << ", " << e.y << ")" << std::endl;
}

void Application::MouseMove(const SDL_MouseMotionEvent& e) {
	std::cout << "Mouse motion: " << e.x << ", " << e.y << ", (" << e.xrel << ", " << e.yrel << ")" << std::endl;
}

void Application::KeyDown(const SDL_KeyboardEvent& e) {
	std::cout << "Key down event: " << e.key << ", " << e.mod << ", " << e.repeat << std::endl;
}

void Application::KeyUp(const SDL_KeyboardEvent& e) {
	std::cout << "Key up event: " << e.key << ", " << e.mod << std::endl;
}
