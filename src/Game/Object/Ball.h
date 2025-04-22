#pragma once
#include "Object.h"
#include "Utils/Vector.h"
#include <cstdint>

class Ball: public GameObject {
public:
	// From GameObject
	void RegisterSelf(ObjectRegistrat& objReg) const override;

private:
	Vector2d pos{};
	uint8_t number{};
};
