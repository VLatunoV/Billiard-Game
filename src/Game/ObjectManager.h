#pragma once
#include "Observer/Observed.h"
#include <vector>

class GameObject;

struct ObservedObjects {
	MouseObserved* mouseObserved;
	KeyboardObserved* keyboardObserved;

	void Validate() const;
};

class ObjectRegistrat {
public:
	ObjectRegistrat(const ObservedObjects& observed);

	void RegisterMouseObserver(const MouseObserver& observer) const;
	void RegisterKeyboardObserver(const KeyboardObserver& observer) const;

private:
	const ObservedObjects observed;
};

class ObjectManager: private ObjectRegistrat {
	friend GameObject;

public:
	ObjectManager(const ObservedObjects& observed);

	void RegisterObject(GameObject& obj);

private:
	void PrivateFunc() const {}
	std::vector<GameObject*> objects;
};
