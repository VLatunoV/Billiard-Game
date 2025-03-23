#pragma once

class ImGuiModule {
public:
	ImGuiModule(const class SdlProvider& sdlProvider, const class GlslProvider& glslProvider);
	~ImGuiModule();
};