#pragma once
#include "state.h"

#include "modules/imgui.h"
#include "modules/sdl.h"

class Application {
public:
	Application();
	~Application();

	int run();

private:
	void startup();
	void shutdown();
	void mainLoop();

	void processEvents();

	State state;

	std::unique_ptr<SdlModule> sdlModule;
	std::unique_ptr<ImGuiModule> imguiModule;

	std::unique_ptr<class GraphicsEngine> graphicsEngine;
};
