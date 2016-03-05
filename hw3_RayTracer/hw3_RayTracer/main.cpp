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

Ray findRayForPixel(Camera camera, Perspective perspective, int rowPixel, int columnPixel) {

	vec3 rayStart = camera.getEye();
	vec3 lookVector = camera.getEye() - camera.getCenter();

	vec3 w = normalize(lookVector);
	vec3 u = normalize(cross(camera.getUp(), w));
	vec3 v = normalize(cross(w, u));

	double rowPixelCenter = rowPixel + 0.5f;
	double columnPixelCenter = columnPixel + 0.5f;

	double tanX = tan(radians(perspective.getFovx()) / 2.0);
	double tanY = tan(radians(perspective.getFovy()) / 2.0);

	double widthCenter = perspective.getW() / 2.0f;
	double heightCenter = perspective.getH() / 2.0f;

	double normalizedXLocation = ((columnPixelCenter - widthCenter) / widthCenter);
	double normalizedYLocation = ((rowPixelCenter - heightCenter) / heightCenter);

	double alpha = tanX * normalizedXLocation;
	double beta = tanY * normalizedYLocation;
	vec3 _rayDirection = vec3(alpha, alpha, alpha) * u + vec3(beta, beta, beta) * v - w;
	vec3 rayDirection = normalize(_rayDirection);

	return Ray(rayStart, rayDirection);
}

void fill(BYTE* pixels, int width, int height, int rowPixel, int columnPixel, RGB color) {
	const int OFFSET = (rowPixel * width + columnPixel) * 3;
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

void countProgress(int rowPixel, int columnPixel, Perspective perspective, int TOTAL_PIXELS, int& reached) {
	int pixelsProcessed = (rowPixel + 1) * perspective.getW() + (columnPixel + 1);
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

	const int BYTES_PER_PIXEL = 3;
	const int TOTAL_PIXELS = perspective.getW() * perspective.getH();
	const int PIXELS_SIZE = TOTAL_PIXELS * BYTES_PER_PIXEL;
	BYTE* pixels = new BYTE[PIXELS_SIZE];
	int reached = -1;
	for (int rowPixel = 0; rowPixel < perspective.getH(); rowPixel++) {
		for (int columnPixel = 0; columnPixel < perspective.getW(); columnPixel++) {
			Ray ray = findRayForPixel(camera, perspective, rowPixel, columnPixel);
			GameObject* closestObject = findClosestIntersection(ray, objects);
			RGB color = findColor(closestObject);

			fill(pixels, perspective.getW(), perspective.getH(), rowPixel, columnPixel, color);
			countProgress(rowPixel, columnPixel, perspective, TOTAL_PIXELS, reached);
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

void test2() {
	Camera camera = initCamera();
	Perspective perspective = initPerspective();
	Ray ray = findRayForPixel(camera, perspective, perspective.getW() / 2, perspective.getH() / 2);
	vector<GameObject*> objects = createObjects();

	cout << "ray:: " << ray.getDirection().x << ", " << ray.getDirection().y << ", " << ray.getDirection().z << endl;
	GameObject* closestObject = findClosestIntersection(ray, objects);
	cout << "closest objects: " << closestObject->getDiffuse().r << endl;
}

void test3() {

}

void main() {
	rayTracer();
	return;
}
