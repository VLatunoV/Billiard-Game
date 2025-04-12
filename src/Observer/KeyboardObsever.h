#pragma once
#include <SDL3/SDL_events.h>

class KeyboardObserver {
public:
	virtual void KeyDown(const SDL_KeyboardEvent& e) = 0;
	virtual void KeyUp(const SDL_KeyboardEvent& e) = 0;
};
