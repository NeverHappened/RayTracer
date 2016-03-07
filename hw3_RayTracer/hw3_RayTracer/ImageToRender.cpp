#include "ImageToRender.h"

ImageToRender::ImageToRender(Perspective perspective) : perspective(perspective) {
	bytesPerPixel = 3;
	totalPixels = perspective.getW() * perspective.getH();
	pixelsSize = totalPixels * bytesPerPixel;

	pixels = new BYTE[pixelsSize];
}

ImageToRender::~ImageToRender() 
{}

void ImageToRender::fill(PixelSample sample, RGB color) {
	const int OFFSET = (sample.rowPixel() * perspective.getW() + sample.columnPixel()) * 3;
	pixels[OFFSET] = color.getB();
	pixels[OFFSET + 1] = color.getG();
	pixels[OFFSET + 2] = color.getR();
}

int ImageToRender::getTotalPixels() const {
	return totalPixels;
}

void ImageToRender::outputToFile(string filename) {
	FreeImageHelper imageHelper(pixels, perspective.getW(), perspective.getH());
	imageHelper.save(filename);
}