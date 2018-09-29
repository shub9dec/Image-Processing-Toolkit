// ################################  Clipping - Stenciling Image   ##############################################

#include<bits/stdc++.h>
#include "Clip_Sten.h"
#include "Image.h"
#include "CompositeImage.h"
#include "Reflection.h"
using namespace std;

Clip_Sten::Clip_Sten(int w, int h):Image(w,h)
{
  w = w;
  h = h;
}
Clip_Sten::~Clip_Sten(){

}


bool Clip_Sten::check(int x,int y,int a,int b,int r){
  int z=(x-a)*(x-a)+(y-b)*(y-b)-r*r;
  if(z<=0){
    return true;
  }
  else{
    return false;
  }
}

void Clip_Sten::generatecircle(int cx,int cy){
    int r=min(floor(getWidth()*0.125),floor(getHeight()*0.125));
    generateColor(r);

}

void Clip_Sten::generate4circle(int w,int h){
      generatecircle(w/2,h/2);
      // generatecircle(w/4,h/4);
      // generatecircle(w/4,(3*h)/4);
      // generatecircle((3*w)/4,h/4);
      // generatecircle((3*w)/4,(3*h)/4);
}

void Clip_Sten::generateColor(int r){
    int h=getHeight();
    int w=getWidth();
    for(int i = 0 ; i < h ; i++){
        for(int j = 0 ; j < w ; j++){
          if (check(h/2,w/2,i,j,r)||check(h/4,w/4,i,j,r)||check((3*h)/4,(3*w)/4,i,j,r)||check(h/4,(3*w)/4,i,j,r)||check((3*h)/4,w/4,i,j,r))
            setColorOfPixel(i,j,Color(0,0,0));
          else
            setColorOfPixel(i,j,Color(255,255,255));
      //    _image[i][j].setX(i+1);
      //    _image[i][j].setY(j+1);
            //cout<<"hi";
        }
      }
    }

Image Clip_Sten::clipping(Image inp){
  int w=getWidth();
  int h=getHeight();
  Image * img=new Image(w,h);
  Color c(0,0,0);
  Color p(255,255,255);
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      if(getPixel(i,j).getColor()==c){
        img->setColorOfPixel(i,j,inp.getPixel(i,j).getColor());
      }
      else{
        img->setColorOfPixel(i,j,p);
      }
    }
  }
  return *img;
}


Image Clip_Sten::stenciling(Image inp){
  int w=getWidth();
  int h=getHeight();
  Image * img=new Image(w,h);
  Color c(0,0,0);
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      if(getPixel(i,j).getColor()==c){
        img->setColorOfPixel(i,j,c);
      }
      else{
        img->setColorOfPixel(i,j,inp.getPixel(i,j).getColor());
      }
    }
  }
  return *img;
}


Image Clip_Sten::reflection(Image img){
   Reflection r(img);
   Image rimg=r.ReflectionY();
   return rimg;
}

CompositeImage Clip_Sten::compose(Image A, Image B, float alpha)
{
  CompositeImage c( A, B, alpha);
  return c;
}
