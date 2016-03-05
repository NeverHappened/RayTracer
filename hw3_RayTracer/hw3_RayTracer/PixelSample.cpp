#include "PixelSample.h"

PixelSample::PixelSample(int pixelRow, int pixelColumn) : pixelRow(pixelRow), pixelColumn(pixelColumn)
{}

PixelSample::~PixelSample()
{}

float PixelSample::getPixelYCenter() const {
	return pixelRow + 0.5f;
}
float PixelSample::getPixelXCenter() const {
	return pixelColumn + 0.5f;
}


int PixelSample::rowPixel() const {
	return pixelRow;
}

int PixelSample::columnPixel() const {
	return pixelColumn;
}