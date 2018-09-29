#ifndef GaussianFilterImage_H
#define GaussianFilterImage_H
#include "Image.h"

class GaussianFilterImage
{
private:
	Image reflectionAboutX(const Image &i);
	Color RgbToHsvUtil(const Color &c);
	Image convertRgbToHsv(const Image &input);
	void colour24Neighborhood(Image &input, const Color &c, int i, int j);
	bool isLocalMaxima(const Image &input, int i, int j);
	Image makeC(const Image &input);
	void applyGaussianFilter(Image &c, const Image &input);


public:
	GaussianFilterImage();
	GaussianFilterImage(const GaussianFilterImage &t);
	~GaussianFilterImage();
	void run(const char* inputFile);

	/* data */
};
#endif
