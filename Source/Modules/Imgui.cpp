#include "Imgui.h"

#include "Interface/SdlProvider.h"
#include "Interface/GlslProvider.h"

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
	ImGui_ImplSDL3_InitForOpenGL(sdlProvider.GetWindow(), sdlProvider.GetGlContext());
	ImGui_ImplOpenGL3_Init(glslProvider.GetGlslVersion());
}

ImGuiModule::~ImGuiModule() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}
