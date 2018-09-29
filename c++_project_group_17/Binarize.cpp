// ################################  BinaryImage ##############################################

#include "Binarize.h"
#include "Image.h"
#include "Color.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stdlib.h>
using namespace std;

Binarize::Binarize()
{

}
Image Binarize::image_binarize(Image &image,int n)
{
	int i,j;
Image ima(image.getWidth(),image.getHeight());
for (int i = 0; i < image.getHeight(); ++i)
{
	for (int j = 0; j < image.getWidth(); ++j)
	{
		Color c = image.getPixel(i,j).getColor();
		int t = (c.getRed() + c.getGreen() + c.getBlue())/3;
		if(t < n)
		{
			Color col(0,0,0);
		ima.setColorOfPixel(i,j,col);
		}
		else
		{
			Color col(255,255,255);
		ima.setColorOfPixel(i,j,col);

		}
	}
}
return ima;
}
