#ifndef IMAGE_H
#define IMAGE_H

#include "Color.h"
#include "Pixel.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
using namespace std;

class Image{
protected:
    int _width;
    int _height;
    Pixel **_image;
public:
    Image();

    Image(int wid, int hei);

    void generateNoiseImage();

    Image(const Image &I);

    void setPixel(int x,int y,Pixel P);
    Pixel getPixel(int x,int y);

    void setColorOfPixel(int x,int y,Color C);

    int getHeight();
    int getWidth();

    void readPPM(const string &inputFile);

    void writePPM(const string &fileName);

    void applyFilter(const Color &c, float opacity);

    virtual ~Image();

    void operator=(const Image &I);

    friend ostream& operator<<(ostream& os, const Image &I);

    friend Image operator +(const Image &i1, const Image &i2);

    friend Image operator *(float alpha, const Image &i1);
    friend Image operator *(const Image &i1, float alpha);

    friend class ConnectedComponentImage;
    friend class GaussianFilterImage;

};

#endif
