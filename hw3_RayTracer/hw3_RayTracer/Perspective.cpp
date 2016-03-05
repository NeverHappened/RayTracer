#include "Perspective.h"

class Perspective {
private:
	int w, h; // width and height 
	float fovy; // For field of view
	float aspect;
	float zNear;
	float zFar;

public:
	Perspective(int w, int h, float fovy, float zNear, float zFar) : 
		w(w), h(h), fovy(fovy), aspect(w / (float) h), zNear(zNear), zFar(zFar)
	{}
	~Perspective()
	{}

	int getW() {
		return w;
	}
	int getH() {
		return h;
	}
	float getFovy() {
		return fovy;
	}
	float getAspect() {
		return aspect;
	}
	float getZNear() {
		return zNear;
	}
	float getZFar() {
		return zFar;
	}
};