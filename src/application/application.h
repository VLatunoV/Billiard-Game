#pragma once
#include "state.h"

#include "modules/imgui.h"
#include "modules/sdl.h"

class Application {
public:
	Application();
	~Application();

	int Run();

private:
	void Startup();
	void Shutdown();
	void MainLoop();

	void ProcessEvents();

	State state;

	std::unique_ptr<SdlModule> sdlModule;
	std::unique_ptr<ImGuiModule> imguiModule;

	std::unique_ptr<class GraphicsEngine> graphicsEngine;
};
