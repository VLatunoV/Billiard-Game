#include "ObjectManager.h"
#include "Object/Object.h"
#include "Observer/MouseObserver.h"
#include "Observer/KeyboardObsever.h"
#include <SDL3/SDL.h>
#include <cassert>

void ObservedObjects::Validate() const {
	assert(mouseObserved);
	assert(keyboardObserved);
}

ObjectRegistrat::ObjectRegistrat(const ObservedObjects& _observed)
	: observed{_observed}
{
	observed.Validate();
}

void ObjectRegistrat::RegisterMouseObserver(const MouseObserver& observer) const {

}

void ObjectRegistrat::RegisterKeyboardObserver(const KeyboardObserver& observer) const {

}

ObjectManager::ObjectManager(const ObservedObjects& observed)
	: ObjectRegistrat{observed}
{}

void ObjectManager::RegisterObject(GameObject& obj) {
	obj.RegisterSelf(*this);
	objects.push_back(&obj);
}
