#pragma once
#include <SDL3/SDL_events.h>

class MouseObserver {
public:
	virtual void MouseDown(const SDL_MouseButtonEvent& e) = 0;
	virtual void MouseUp(const SDL_MouseButtonEvent& e) = 0;
	virtual void MouseMove(const SDL_MouseMotionEvent& e) = 0;
};
