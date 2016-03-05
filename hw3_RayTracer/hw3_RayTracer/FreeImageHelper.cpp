#include "FreeImageHelper.h"
#include <string>

class FreeImageHelper {
private:
	FIBITMAP* img;
public:
	FreeImageHelper(BYTE* pixels, int width, int height) {
		img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	}
	~FreeImageHelper() {
		FreeImage_DeInitialise();
		free(img); // WTF? :D
	}

	void save(string as) {
		FreeImage_Save(FIF_PNG, img, as.c_str(), 0);
	}
};