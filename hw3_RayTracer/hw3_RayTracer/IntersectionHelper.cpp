#include "IntersectionHelper.h"

Intersection IntersectionHelper::findClosestIntersection(Ray ray, std::vector<GameObject*> objects) {
	double minDistance = -1;
	GameObject* closestIntersected = NULL;

	for (GameObject* obj : objects) {
		double distance = obj->intersectionDistance(ray);
		if (minDistance == -1 && distance != -1) {
			minDistance = distance;
			closestIntersected = obj;
		}
		else if (distance < minDistance) {
			minDistance = distance;
			closestIntersected = obj;
		}
	}

	if (minDistance == -1) {
		return Intersection(NULL, -1.0, vec3(0, 0, 0));
	}
	else {
		return Intersection(closestIntersected, minDistance, ray.getStart() + ((float)minDistance-0.01f) * ray.getDirection());
	}
}


IntersectionHelper::IntersectionHelper()
{};

IntersectionHelper::~IntersectionHelper()
{};