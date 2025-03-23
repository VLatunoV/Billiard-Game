#pragma once

class SdlProvider {
public:
	virtual struct SDL_Window* getWindow() const = 0;
	virtual struct SDL_GLContextState* getGlContext() const = 0;
};
