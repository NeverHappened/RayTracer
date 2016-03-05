#pragma once

#include "Ray.h"

class GameObject {
public:
	virtual bool intersects(Ray ray);
};