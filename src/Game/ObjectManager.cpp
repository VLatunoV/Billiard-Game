#include "ObjectManager.h"
#include "Observer/MouseObserver.h"
#include "Observer/KeyboardObsever.h"
#include <SDL3/SDL.h>

ObjectManager::ObjectManager(MouseObserved* _mouseObserved, KeyboardObserved* _keyboardObserved)
	: mouseObserved{_mouseObserved}
	, keyboardObserved{_keyboardObserved}
{}

void ObjectManager::RegisterObject(GameObject& obj) {
	objects.push_back(&obj);
}

void ObjectManager::RegisterMouseObserver(const MouseObserver& observer) const {

}

void ObjectManager::RegisterKeyboardObserver(const KeyboardObserver& observer) const {

}