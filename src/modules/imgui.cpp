#include "imgui.h"

#include "interface/sdl_provider.h"
#include "interface/glsl_provider.h"

#include "../imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

ImGuiModule::ImGuiModule(const SdlProvider& sdlProvider, const GlslProvider& glslProvider) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForOpenGL(sdlProvider.getWindow(), sdlProvider.getGlContext());
	ImGui_ImplOpenGL3_Init(glslProvider.getGlslVersion());
}

ImGuiModule::~ImGuiModule() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}
