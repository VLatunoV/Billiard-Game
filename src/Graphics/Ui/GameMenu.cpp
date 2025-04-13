#include "GameMenu.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>

void GameMenu::PreRender() {
	const auto& io = ImGui::GetIO();
	// Our state
	static bool show_demo_window = false;
	static bool show_another_window = false;

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	const char windowName[] = "Testing window";
	static float f = 0.0f;
	static int counter = 0;

	ImGui::SetNextWindowPos(ImVec2{0.0f, 0.0f});
	ImGui::SetNextWindowCollapsed(false);
	ImGui::SetNextWindowSize(ImVec2{0, io.DisplaySize.y});
	ImGui::Begin(windowName, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);                          // Create a window called "Hello, world!" and append into it.
	windowSize = ImGui::GetWindowSize();

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &show_another_window);

	ImGui::SliderFloat("Radius", &state.circleRad, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&state.clearColor); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	// 3. Show another simple window.
	if (show_another_window) {
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	ImGui::GetForegroundDrawList()->AddText(ImVec2{io.MousePos.x, -10 + io.MousePos.y}, ImColor(255.0f, 0.0f, 0.0f, 255.0f), "My text");
	ImGui::Render();
}

void GameMenu::Render() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

const UiState& GameMenu::GetUiState() const {
	return state;
}

ImVec2 GameMenu::GetSize() const {
	return windowSize;
}
