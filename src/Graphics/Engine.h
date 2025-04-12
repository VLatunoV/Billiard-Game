#pragma once
#include "Modules/Sdl.h"

class GraphicsEngine {
public:
	GraphicsEngine(SdlProvider& sdlProvider);
	~GraphicsEngine();

	void DrawFrame();

private:
	void DrawFrameInternal();

	SDL_Window* const window = nullptr;
};
