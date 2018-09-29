#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Image.h"
#include "Color.h"
#include "Pixel.h"

using namespace std;

class Histogram
{
  private:
    vector<int> histogram;
    vector<int> threshold;
    Image Main_Img;
    vector< vector<int> > brightness;
    int T1,T2;
  public:
    Histogram();
    ~Histogram();
    void setThreshold();

    Histogram(Image i);
    int getThreshold();
    vector< vector<int> > getBrightness();
    void CreateImage_CD();
    void printHist();
    void run();

};

#endif
