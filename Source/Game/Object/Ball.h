#pragma once
#include "Object.h"

class Ball: public GameObject {
public:
	// From GameObject
	void Register(ObjectManager&) const override;
};
