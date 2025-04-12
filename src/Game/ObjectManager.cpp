#include "ObjectManager.h"
#include <SDL3/SDL.h>

void ObjectManager::RegisterObject(GameObject& obj) {
	objects.push_back(&obj);
}

void ObjectManager::MouseDown(const SDL_MouseButtonEvent& e) {

}

void ObjectManager::MouseUp(const SDL_MouseButtonEvent& e) {

}

void ObjectManager::MouseMove(const SDL_MouseMotionEvent& e) {

}
