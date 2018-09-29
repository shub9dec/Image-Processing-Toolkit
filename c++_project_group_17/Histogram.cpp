#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Histogram.h"
#include "Image.h"
#include "Color.h"
#include "Pixel.h"
#include "Reflection.h"
#include "CompositeImage.h"
#include "ConnectedComponent.h"
#include "Binarize.h"

using namespace std;

Histogram::Histogram(){}

Histogram::~Histogram(){}

Histogram::Histogram(Image i):brightness(i.getHeight(), vector <int> (i.getWidth()))
{
   Main_Img=i;
  int h = i.getHeight();
  int w = i.getWidth();
  for(int k = 0; k < h; k++)
  {
    for(int j = 0; j < w; j++)
    {
      Color c;
      c = i.getPixel(k,j).getColor();
      brightness[k][j] = (c.getRed() + c.getBlue() + c.getGreen())/3;
    }
  }
  for(int i=0;i<256;i++){histogram.push_back(0);}
  for(int i = 0; i < h; i++)
  {
    for(int j = 0; j < w; j++)
    {
      histogram[brightness[i][j]]++;
    }
  }

  for(int i = 3; i < 252; i++)
  {
    if(histogram[i] < histogram[i-1]&& histogram[i] < histogram[i-2]&&histogram[i] < histogram[i-3]
       && histogram[i+1] > histogram[i] &&histogram[i+2] > histogram[i]&& histogram[i+3] > histogram[i])
      threshold.push_back(i);
  }

}

int Histogram::getThreshold()
{
  return threshold[threshold.size()/2];
}

void Histogram::setThreshold(){
   T1=Main_Img.getWidth()*Main_Img.getHeight();
   T2=Main_Img.getWidth()*Main_Img.getHeight();

    for(int i=0;i<threshold.size();i++){
      if(threshold[i]<T1){
             T2=T1;
             T1=threshold[i];
          }
      else if (threshold[i] < T2 && threshold[i] != T1)
          T2 = threshold[i];
      }
}

vector< vector<int> > Histogram::getBrightness()
{
  return brightness;
}


void Histogram::CreateImage_CD(){
   Color temp;int bri;

   Image C(Main_Img.getWidth(),Main_Img.getHeight());
   Image D(Main_Img.getWidth(),Main_Img.getHeight());


   for(int i=0;i<Main_Img.getHeight();i++){
      for(int j=0;j<Main_Img.getWidth();j++){

         temp=Main_Img.getPixel(i,j).getColor();
         bri=(temp.getRed()+temp.getBlue()+temp.getGreen())/3;
         if(T1!=Main_Img.getWidth()*Main_Img.getHeight() && T2!=Main_Img.getWidth()*Main_Img.getHeight()){
            if(bri<T1){
            C.setPixel(i,j,Pixel(i,j,Color(0,0,255)));
            }
            else {
               C.setPixel(i,j,Pixel(i,j,Color(255,255,255)));
            }

            if(bri<T2){
               D.setPixel(i,j,Pixel(i,j,Color(255,255,0)));
            }
            else {
               D.setPixel(i,j,Pixel(i,j,Color(255,255,255)));
            }
         }
      }
   }
   if(T1==Main_Img.getWidth()*Main_Img.getHeight() && T2==Main_Img.getWidth()*Main_Img.getHeight()){
        Reflection ref(Main_Img);
           C=ref.ReflectionX();
           D=ref.ReflectionY();
        }
   CompositeImage Com(D,C,0.2);
   Com.writePPM("output_task5_imt2016091.ppm");
}

void Histogram::printHist() {
  int width = 255;
  int height = 0;
  for(int i = 0; i < width; i++) {
     if(height<histogram[i]){
        height=histogram[i];
     }
  }
  Image image(width, height);
  for(int i = 0; i < height; i++) {
     for(int j = 0; j < width; j++) {
       if(histogram[j] >= height - i) {
         Color c;
         c = Color(0, 0, 0);
         image.setColorOfPixel(i, j, c);
       } else {
         Color c;
         c = Color(255, 255, 255);
         image.setColorOfPixel(i, j, c);
       }
     }
  }
    image.writePPM("Histogram.ppm");
 }

void Histogram::run(){
       setThreshold();
       CreateImage_CD();
       printHist();
}
