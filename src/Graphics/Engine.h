#pragma once
#include "Modules/Sdl.h"

class GraphicsEngine {
public:
	GraphicsEngine(SdlProvider& sdlProvider);
	~GraphicsEngine();

	void DrawFrame();

private:
	void PreRender();
	void Render();
	void PostRender();

	SDL_Window* const window = nullptr;

	std::unique_ptr<class GameMenu> gameUi;
};
