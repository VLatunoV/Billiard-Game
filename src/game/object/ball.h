#pragma once
#include "object.h"

class Ball: public GameObject {
	// From GameObject
	void Register(ObjectManager&) const override;
};
