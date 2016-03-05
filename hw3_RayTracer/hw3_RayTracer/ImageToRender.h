#pragma once

#include "Perspective.h"
#include "FreeImage.h"
#include "RGB.h"
#include "PixelSample.h"

class ImageToRender {
private:
	Perspective perspective;
	int bytesPerPixel;
	int totalPixels;
	int pixelsSize;
	BYTE* pixels;
public:
	ImageToRender(Perspective perspective);
	~ImageToRender();
	
	int getTotalPixels() const;
	void fill(PixelSample sample, RGB color);
	void outputToFile(string filename);
};