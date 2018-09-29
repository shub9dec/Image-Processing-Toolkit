#ifndef part1a_h
#define part1a_h
#include<bits/stdc++.h>
#include "Image.h"
#include "CompositeImage.h"
using namespace std;
class Clip_Sten:public Image{
private:
  int w,h;
//   Image *d;
public:
    // Clip_Sten(float x,float y):w(x),h(y){};
    Clip_Sten(int x,int y);
    ~Clip_Sten();
    Clip_Sten(const Clip_Sten &p);
    bool check(int x,int y, int z, int q, int u);
    void generatecircle(int w,int h);
    void generate4circle(int w, int h);
    void generateColor( int r);
    Image clipping(Image u);
    Image stenciling( Image u);
    Image reflection(Image k);
    CompositeImage compose(Image A, Image B, float alpha);
};
#endif
