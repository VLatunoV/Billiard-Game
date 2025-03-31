#pragma once

class ObjectManager;

class GameObject {
public:
	virtual ~GameObject() = default;
	virtual void Register(ObjectManager&) const = 0;
};
