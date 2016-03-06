#pragma once

#include "GameObject.h"
#include "Intersection.h"
#include <vector>

class IntersectionHelper {
public:
	IntersectionHelper();
	virtual ~IntersectionHelper();
public:
	static Intersection findClosestIntersection(Ray ray, std::vector<GameObject*> objects);
};
