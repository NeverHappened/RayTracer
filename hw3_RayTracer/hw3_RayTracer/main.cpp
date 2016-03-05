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
#include "Sampler.h"

using namespace std;
using namespace glm;

vector<GameObject*> createObjects() {
	vector<GameObject*> res;

	Sphere* s = new Sphere(vec3(0.0f, 0.0f, 0.0f), 0.5, vec3(255, 0, 0));

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
	int w = 800, h = 600;
	float aspect = w / (float)h;
	float fovy = 45;
	float fovyRadians = radians(fovy);
	float fovx = degrees(2 * atan(tan(fovyRadians / 2.0f) * aspect));

	float zNear = 0.1f;
	float zFar = 99.0f;

	return Perspective(w, h, fovy, fovx, zNear, zFar);
}

Ray findRayForPixel(Camera camera, Perspective perspective, PixelSample sample) {

	vec3 rayStart = camera.getEye();
	vec3 lookVector = camera.getEye() - camera.getCenter();

	vec3 w = normalize(lookVector);
	vec3 u = normalize(cross(camera.getUp(), w));
	vec3 v = normalize(cross(w, u));

	double tanX = tan(radians(perspective.getFovx()) / 2.0);
	double tanY = tan(radians(perspective.getFovy()) / 2.0);

	double widthCenter = perspective.getW() / 2.0f;
	double heightCenter = perspective.getH() / 2.0f;

	double normalizedXLocation = ((sample.getPixelXCenter() - widthCenter) / widthCenter);
	double normalizedYLocation = ((sample.getPixelYCenter() - heightCenter) / heightCenter);

	double alpha = tanX * normalizedXLocation;
	double beta = tanY * normalizedYLocation;
	vec3 _rayDirection = vec3(alpha, alpha, alpha) * u + vec3(beta, beta, beta) * v - w;
	vec3 rayDirection = normalize(_rayDirection);

	return Ray(rayStart, rayDirection);
}

void fill(BYTE* pixels, int width, int height, PixelSample sample, RGB color) {
	const int OFFSET = (sample.rowPixel() * width + sample.columnPixel()) * 3;
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

void countProgress(PixelSample sample, Perspective perspective, int TOTAL_PIXELS) {
	static int reached = -1;

	int pixelsProcessed = (sample.rowPixel() + 1) * perspective.getW() + (sample.columnPixel() + 1);
	int percent = floor((pixelsProcessed / (double)TOTAL_PIXELS) * 100);
	if (percent / 10 != reached && percent % 10 == 0) {
		reached += 1;
		cout << percent << " % of pixels processed." << endl;
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

	Sampler sampler(perspective.getW(), perspective.getH());

	const int BYTES_PER_PIXEL = 3;
	const int TOTAL_PIXELS = perspective.getW() * perspective.getH();
	const int PIXELS_SIZE = TOTAL_PIXELS * BYTES_PER_PIXEL;
	BYTE* pixels = new BYTE[PIXELS_SIZE];

	while (sampler.anySamples()) {
		PixelSample sample = sampler.getSample();

		Ray ray = findRayForPixel(camera, perspective, sample);
		GameObject* closestObject = findClosestIntersection(ray, objects);
		RGB color = findColor(closestObject);

		fill(pixels, perspective.getW(), perspective.getH(), sample, color);
		countProgress(sample, perspective, TOTAL_PIXELS);
	}

	FreeImageHelper imageHelper(pixels, perspective.getW(), perspective.getH());
	imageHelper.save("test_image.png");
}




void main() {
	rayTracer();
	return;
}
