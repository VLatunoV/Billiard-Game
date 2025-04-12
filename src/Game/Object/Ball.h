#pragma once
#include "Object.h"
#include "Utils/Vector.h"
#include <cstdint>

class Ball: public GameObject {
public:
	// From GameObject

private:
	Vector2d pos{};
	uint8_t number{};
};
