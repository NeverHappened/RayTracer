#include "Perspective.h"

Perspective::Perspective(int w, int h, float fovy, float fovx, float zNear, float zFar) :
	w(w), h(h), fovy(fovy), fovx(fovx), zNear(zNear), zFar(zFar)
{
	aspect = w / (float)h;
}

Perspective::~Perspective()
{}

int Perspective::getW() {
	return w;
}
int Perspective::getH() {
	return h;
}
float Perspective::getFovy() {
	return fovy;
}
float Perspective::getFovx() {
	return fovx;
}
float Perspective::getAspect() {
	return aspect;
}
float Perspective::getZNear() {
	return zNear;
}
float Perspective::getZFar() {
	return zFar;
}
