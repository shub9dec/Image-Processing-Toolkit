#include <iostream>
#include "Image.h"

using namespace std;
#ifndef COMPOSITE_IMAGE_H
#define COMPOSITE_IMAGE_H
class CompositeImage:public Image
{
public:
	CompositeImage();
	CompositeImage(const Image &A, const Image &B, float alpha);
	CompositeImage(const CompositeImage &c);
	~CompositeImage();

	/* data */
};
#endif