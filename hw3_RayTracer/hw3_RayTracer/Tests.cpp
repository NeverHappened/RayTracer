/*#include "Ray.h"
#include "Sphere.h"
#include <iostream>
#include "main.cpp"

using namespace std;

void test() {
	Ray ray(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, -1.0f));
	Sphere sphere(vec3(0.0f, 0.0f, 0.0f), 2.0f, vec3(255, 255, 0));

	cout << "intersection distance???:: " << sphere.intersectionDistance(ray) << endl;
}

void test2() {
	Camera camera = initCamera();
	Perspective perspective = initPerspective();
	Ray ray = findRayForPixel(camera, perspective, PixelSample(perspective.getW() / 2, perspective.getH() / 2));
	vector<GameObject*> objects = createObjects();

	cout << "ray:: " << ray.getDirection().x << ", " << ray.getDirection().y << ", " << ray.getDirection().z << endl;
	GameObject* closestObject = findClosestIntersection(ray, objects);
	cout << "closest objects: " << closestObject->getDiffuse().r << endl;
}


void test3() {

}*/