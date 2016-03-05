#pragma once

#include "Ray.h"

class GameObject {
protected:
	vec3 diffuse;
public:
	virtual double intersectionDistance(Ray ray) = 0;
	virtual vec3 getDiffuse() const;
};
