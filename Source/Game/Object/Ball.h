#pragma once
#include "Object.h"

class Ball: public GameObject {
	// From GameObject
	void Register(ObjectManager&) const override;
};
