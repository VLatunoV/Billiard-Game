#include "sdl.h"

#include "utils/exception.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"

SdlModule::SdlModule() {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
		Raise<InitializationException>(SDL_GetError());
	}

	// GL 3.0 + GLSL 130
	glslVersion = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
	window.reset(SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", 1280, 720, windowFlags));
	if (window == nullptr) {
		Raise<InitializationException>(SDL_GetError());
	}
	SDL_SetWindowPosition(window.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	glContext.reset(SDL_GL_CreateContext(window.get()));
	if (glContext == nullptr) {
		Raise<InitializationException>(SDL_GetError());
	}

	SDL_GL_MakeCurrent(window.get(), glContext.get());
	SDL_GL_SetSwapInterval(1); // Enable vsync
	SDL_ShowWindow(window.get());
}

SdlModule::~SdlModule() {
	SDL_Quit();
}

SDL_Window* SdlModule::GetWindow() const {
	return window.get();
}

SDL_GLContextState* SdlModule::GetGlContext() const {
	return glContext.get();
}

const char* SdlModule::GetGlslVersion() const {
	return glslVersion;
}

void SdlModule::WindowDeleter::operator()(SDL_Window* window) {
	if (window) SDL_DestroyWindow(window);
}

void SdlModule::GlContextDeleter::operator()(SDL_GLContextState* glContext) {
	if (glContext) SDL_GL_DestroyContext(glContext);
}
