#pragma once
#include "interface/sdl_provider.h"
#include "interface/glsl_provider.h"

#include <memory>

struct SDL_Window;
struct SDL_GLContextState;

class SdlModule
	: public SdlProvider
	, public GlslProvider
{
public:
	SdlModule();
	~SdlModule();

	// From SdlProvider
	SDL_Window* getWindow() const override;
	SDL_GLContextState* getGlContext() const override;

	// From GlslProvider
	const char* getGlslVersion() const override;

private:
	struct WindowDeleter {
		void operator()(SDL_Window*);
	};
	struct GlContextDeleter {
		void operator()(SDL_GLContextState*);
	};

	std::unique_ptr<SDL_Window, WindowDeleter> window;
	std::unique_ptr<SDL_GLContextState, GlContextDeleter> glContext;

	const char* glslVersion{};
};
