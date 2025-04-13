#pragma once
#include "State.h"

#include "Observer/Observed.h"
#include "Observer/KeyboardObsever.h"
#include "Observer/MouseObserver.h"

#include <memory>

class Application
	: public Observed<KeyboardObserver>
	, public Observed<MouseObserver>
	, public KeyboardObserver
	, public MouseObserver
{
public:
	Application();
	~Application();

	int Run();

private:
	void Startup();
	void Shutdown();

	void MainLoop();
	void ProcessEvents();
	void HandleInputEvents(SDL_Event& event);

	void RegisterMouseObserver(MouseObserver* o);
	void RegisterKeyboardObserver(KeyboardObserver* o);
	void RegisterObservers();

	// From KeyboardObserver
	using Observed<KeyboardObserver>::Notify;
	void KeyDown(const SDL_KeyboardEvent& e) override;
	void KeyUp(const SDL_KeyboardEvent& e) override;

	// From MouseObserver
	using Observed<MouseObserver>::Notify;
	void MouseDown(const SDL_MouseButtonEvent& e) override;
	void MouseUp(const SDL_MouseButtonEvent& e) override;
	void MouseMove(const SDL_MouseMotionEvent& e) override;

	State state;

	std::unique_ptr<class SdlModule> sdlModule;
	std::unique_ptr<class ImGuiModule> imguiModule;

	std::unique_ptr<class GraphicsEngine> graphicsEngine;
	std::unique_ptr<class ObjectManager> objectManager;
};
