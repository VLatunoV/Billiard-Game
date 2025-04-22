#pragma once
#include "Modules/Sdl.h"

struct FrameData;

class GraphicsEngine {
public:
	GraphicsEngine(SdlProvider& sdlProvider);
	~GraphicsEngine();

	void DrawFrame();

private:
	void PopulateFrameData(FrameData& frameData);
	void PreRender(const FrameData& frameData);
	void Render(const FrameData& frameData);
	void PostRender(const FrameData& frameData);

	SDL_Window* const window;

	std::unique_ptr<class Scene> gameScene;
};
