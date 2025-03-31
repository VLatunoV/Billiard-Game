#pragma once

class SdlProvider {
public:
	virtual struct SDL_Window* GetWindow() const = 0;
	virtual struct SDL_GLContextState* GetGlContext() const = 0;
};
