#include <iostream>
#include "FreeImageHelper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "GameObject.h"
#include "Sphere.h"
#include "Camera.h"
#include "Perspective.h"
#include "RGB.h"

using namespace std;
using namespace glm;

vector<GameObject*> createObjects() {
	vector<GameObject*> res;

	Sphere* s = new Sphere(vec3(0.0f, 0.0f, 0.0f), 1, vec3(255, 0, 0));

	res.push_back(s);
	return res;
}

Camera initCamera() {
	vec3 eyeinit(0.0, 0.0, 5.0); // Initial eye position, also for resets
	vec3 upinit(0.0, 1.0, 0.0); // Initial up position, also for resets
	vec3 center(0.0, 0.0, 0.0); // Center look at point 

	return Camera(eyeinit, upinit, center);
}

Perspective initPerspective() {
	int w = 400, h = 400;
	float aspect = w / (float)h;
	float fovx = 90.0;
	float fovy = fovx / aspect;

	float zNear = 0.1;
	float zFar = 99.0;

	return Perspective(w, h, fovy, fovx, zNear, zFar);
}

Ray findRayForPixel(Camera camera, Perspective perspective, int i, int j) {

	vec3 rayStart = camera.getEye();
	vec3 lookVector = camera.getEye() - camera.getCenter();

	vec3 w = normalize(lookVector);
	vec3 u = normalize(cross(camera.getUp(), w));
	vec3 v = normalize(cross(w, u));

	double pixelCenterI = i + 0.5f;
	double pixelCenterJ = j + 0.5f;

	double tanX = tan(radians(perspective.getFovx() / 2));
	double tanY = tan(radians(perspective.getFovy() / 2));

	double widthCenter = perspective.getW() / 2.0f;
	double heightCenter = perspective.getH() / 2.0f;

	double normalizedXLocation = ((pixelCenterI - widthCenter) / widthCenter);
	double normalizedYLocation = ((heightCenter - pixelCenterJ) / heightCenter);

	double alpha = tanX * normalizedXLocation;
	double beta = tanY * normalizedYLocation;
	vec3 _rayDirection = vec3(alpha, alpha, alpha) * u + vec3(beta, beta, beta) * v - w;
	vec3 rayDirection = normalize(_rayDirection);

	return Ray(rayStart, rayDirection);
}

void fill(BYTE* pixels, int width, int height, int i, int j, RGB color) {
	const int OFFSET = (i * width + j) * 3;
	pixels[OFFSET] = color.getB();
	pixels[OFFSET + 1] = color.getG();
	pixels[OFFSET + 2] = color.getR();
}

GameObject* findClosestIntersection(Ray ray, vector<GameObject*> objects) {
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

	return closestIntersected;
}

RGB findColor(GameObject* obj) {
	if (obj == NULL) {
		return RGB(25, 25, 25);
	}
	else {
		return RGB(obj->getDiffuse());
	}
}

void rayTracer() {
	// OK THATS A START, BUT
	// need to describe high-level algorithm of ray tracer

	// hmmmmm
	// 1) create some objects and put them in a stack (WORLD COORDINATES)
	// 2) create camera
	// 3) create look at transformation matrix
	// 4) NOPE - dont need to implement the old rasterization algorithm
	// 4) create basic variables for viewing - width, height, fovy, fovx, near, far planes
	// 5) create pixel array
	// 6) iterate over each pixel
	// 7) shoot rays in them
	// 8) check for intersections with objects
	// 9) fill pixel array
	// 10) output pixel array in file
	// 11) watch render!!!

	vector<GameObject*> objects = createObjects();
	Camera camera = initCamera();
	Perspective perspective = initPerspective();

	const int BYTES_PER_PIXEL = 3;
	const int PIXELS_SIZE = perspective.getW() * perspective.getH() * BYTES_PER_PIXEL;
	BYTE* pixels = new BYTE[PIXELS_SIZE];
	for (int i = 0; i < perspective.getH(); i++) {
		for (int j = 0; j < perspective.getW(); j++) {
			Ray ray = findRayForPixel(camera, perspective, i, j);
			GameObject* closestObject = findClosestIntersection(ray, objects);
			RGB color = findColor(closestObject);

			fill(pixels, perspective.getW(), perspective.getH(), i, j, color);
		}
	}

	FreeImageHelper imageHelper(pixels, perspective.getW(), perspective.getH());
	imageHelper.save("test_image.png");
}

void test() {
	Ray ray(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, -1.0f));
	Sphere sphere(vec3(0.0f, 0.0f, 0.0f), 2.0f, vec3(255, 255, 0));

	cout << "intersection distance???:: " << sphere.intersectionDistance(ray) << endl;
}

void main() {
	rayTracer();
	return;
}
