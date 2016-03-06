#include "FreeImageHelper.h"

FreeImageHelper::FreeImageHelper(BYTE* pixels, int width, int height) {
	img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
}

FreeImageHelper::~FreeImageHelper() {
	FreeImage_DeInitialise();
}

void FreeImageHelper::save(string withName) {
	FreeImage_Save(FIF_PNG, img, withName.c_str(), 0);
}
