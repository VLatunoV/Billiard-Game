#pragma once
#include "Game/ObjectManager.h"

class GameObject {
public:
	virtual ~GameObject() = default;

	virtual void RegisterSelf(ObjectRegistrat& objReg) const = 0;
};
