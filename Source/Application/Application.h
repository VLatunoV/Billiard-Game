#pragma once
#include "State.h"

#include "Modules/Imgui.h"
#include "Modules/Sdl.h"

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
