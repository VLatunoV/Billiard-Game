#pragma once
#include "Observer/MouseObserver.h"
#include <vector>

class GameObject;

class ObjectManager: public MouseObserver {
public:
	void RegisterObject(GameObject& obj);

private:
	// From MouseObserver
	void MouseDown(const SDL_MouseButtonEvent& e) override;
	void MouseUp(const SDL_MouseButtonEvent& e) override;
	void MouseMove(const SDL_MouseMotionEvent& e) override;

private:
	std::vector<GameObject*> objects;
};
