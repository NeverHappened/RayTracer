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
#include "ImageToRender.h"
#include "Shader.h"

using namespace std;
using namespace glm;

vector<GameObject*> createObjects() {
	vector<GameObject*> res;

	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	float radius = 0.5f;
	vec4 ambient(0.2f, 0.2f, 0.2f, 1.0f);
	vec4 diffuse(0.5f, 0.5f, 0.5f, 1.0f);
	vec4 specular(1.0f, 1.0f, 1.0f, 1.0f);
	float shininess(100.0f);
	Sphere* s = new Sphere(position, radius, ambient, diffuse, specular, shininess);

	res.push_back(s);
	return res;
}

Camera initCamera() {
	vec3 eyeinit(0.0, 0.0, 5.0); // Initial eye position, also for resets
	vec3 upinit(0.0, 1.0, 0.0); // Initial up position, also for resets
	vec3 center(0.0, 0.0, 0.0); // Center look at point 

	return Camera(eyeinit, upinit, center);
}

vector<Light> initLights() {
	vector<Light> lights;

	vec4 position(0.6, 0.0, 0.1, 0);
	vec4 color(1.0f, 0.5f, 1.0f, 1.0f);
	Light light(position, color);
	lights.push_back(light);

	return lights;
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

void countProgress(PixelSample sample, ImageToRender image, Perspective perspective) {
	static int reached = -1;

	int pixelsProcessed = (sample.rowPixel() + 1) * perspective.getW() + (sample.columnPixel() + 1);
	int percent = (int) floor((pixelsProcessed / (double)image.getTotalPixels()) * 100);
	if (percent / 10 != reached && percent % 10 == 0) {
		reached += 1;
		cout << percent << " % of pixels processed." << endl;
	}
}

void rayTracer() {
	vector<GameObject*> objects = createObjects();
	Camera camera = initCamera();
	Perspective perspective = initPerspective();
	Sampler sampler(perspective.getW(), perspective.getH());
	ImageToRender image(perspective);
	vector<Light> lights = initLights();
	Shader shader = Shader(lights);

	while (sampler.anySamples()) {
		PixelSample sample = sampler.getSample();
		Ray ray = findRayForPixel(camera, perspective, sample);
		GameObject* closestObject = findClosestIntersection(ray, objects);
		RGB color = shader.shade(closestObject, ray);

		image.fill(sample, color);
		countProgress(sample, image, perspective);
	}

	image.outputToFile("test_image.png");
}


void main() {
	rayTracer();
	return;
}
