#pragma once
#include "Observer/Observed.h"
#include <vector>

class GameObject;

class ObjectManager {
public:
	ObjectManager(MouseObserved* mouseObserved, KeyboardObserved* keyboardObserved);

	void RegisterObject(GameObject& obj);

private:
	void RegisterMouseObserver(const MouseObserver& observer) const;
	void RegisterKeyboardObserver(const KeyboardObserver& observer) const;

	std::vector<GameObject*> objects;
	MouseObserved* const mouseObserved;
	KeyboardObserved* const keyboardObserved;
};
