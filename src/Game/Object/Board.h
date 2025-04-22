#pragma once
#include "Ball.h"
#include "Object.h"
#include "Observer/MouseObserver.h"

#include <vector>

class BilliardBoard: public GameObject, public MouseObserver {
private:
	// From GameObject
	void RegisterSelf(ObjectRegistrat& objReg) const;

	// From MouseObserver
	void MouseDown(const SDL_MouseButtonEvent& e) override;
	void MouseUp(const SDL_MouseButtonEvent& e) override;
	void MouseMove(const SDL_MouseMotionEvent& e) override;

	std::vector<Ball> balls;
};
