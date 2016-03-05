#include <iostream>
#include "FreeImageHelper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "GameObject.h"
#include "Sphere.h"
#include "Camera.h"
#include "Perspective.h"

using namespace std;
using namespace glm;

vector<GameObject> createObjects() {
	vector<GameObject> res;

	Sphere s(vec3(0, 0, -1), 0.5);

	res.push_back(s);

	return res;
}

Camera initCamera() {
	vec3 eyeinit(0.0, 0.0, 5.0); // Initial eye position, also for resets
	vec3 upinit(0.0, 1.0, 0.0); // Initial up position, also for resets
	vec3 center(0.0, 0.0, 0.0); // Center look at point 

	return Camera(eyeinit, upinit, eyeinit - center);
}

Perspective initPerspective() {
	int w = 600, h = 400; // width and height 
	float fovy = 90.0; // For field of view
	float aspect = w / (float)h;
	float zNear = 0.1;
	float zFar = 99.0;

	return Perspective(w, h, fovy, zNear, zFar);
}

Ray findRayForPixel(Camera camera, Perspective perspective, int i, int j) {

}

void main() {
	cout << "Hi, dima :)" << endl;
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

	vector<GameObject> objects = createObjects();
	Camera camera = initCamera();
	Perspective perspective = initPerspective();

	const int BYTES_PER_PIXEL = 3;
	const int PIXELS_SIZE = perspective.getW() * perspective.getH() * BYTES_PER_PIXEL;
	BYTE* pixels = new BYTE[PIXELS_SIZE];
	for (int i = 0; i < perspective.getH(); i++) { // j is a row
		for (int j = 0; j < perspective.getW(); j++) {

			Ray ray = findRayForPixel(camera, perspective, i, j);
		}
	}
}