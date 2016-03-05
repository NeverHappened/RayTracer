#include "Perspective.h"

Perspective::Perspective(int w, int h, float fovy, float zNear, float zFar) :
	w(w), h(h), fovy(fovy), aspect(w / (float) h), zNear(zNear), zFar(zFar)
{}

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
float Perspective::getAspect() {
	return aspect;
}
float Perspective::getZNear() {
	return zNear;
}
float Perspective::getZFar() {
	return zFar;
}
