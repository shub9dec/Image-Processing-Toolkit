#include <bits/stdc++.h>
#include "Image.h"
#include "Color.h"
#include "GaussianFilterImage.h"
#include "Histogram.h"
#include "Reflection.h"
#include "ConnectedComponentImage.h"
#include "ScaledImage.h"
#include "Clip_Sten.h"
#include "ConnectedComponent.h"
#include "Binarize.h"

using namespace std;

void PartA(const char* inputFile){
    GaussianFilterImage IMT2016070;
    IMT2016070.run(inputFile);
    return ;
}
void PartB(const char* inputFile)
{
    Image *I=new Image();
    I->readPPM(inputFile);
    Histogram his(*I);
    his.run();
    return;
}

void PartC(const char* inputFile){
   ConnectedComponentImage IMT2016130;
   IMT2016130.Run6(inputFile);
   return;
}

void PartD(const char* inputFile){
   Image I;
   I.readPPM(inputFile);
   ScaledImage* Im=new ScaledImage(I);
   Im->run();
   return;
}

void PartE(const char* inputFile){
   Image *img = new Image();
   img->readPPM(inputFile);
   string s;
   int w,h;
   w=img->getWidth();
   h=img->getHeight();
   Clip_Sten* pmg=new Clip_Sten(w,h);
   pmg->generate4circle(w,h);
   pmg->writePPM("output_task1_imt201649_circle.ppm");
   Image clip=pmg->clipping(*img);
   clip.writePPM("output_task1_imt201649_clipping.ppm");
   Image reflect = pmg->reflection(*img);
   reflect.writePPM("output_task1_imt201649_reflection.ppm");
   Image stencil = pmg->stenciling(reflect);
   stencil.writePPM("output_task1_imt201649_stenciling.ppm");
   CompositeImage comp(clip,stencil,0.5);
   comp.writePPM("output_task1_imt201649_final.ppm");
   return;
}
void PartF(const char* inputFile){
   Image *img=new Image();
   img->readPPM(inputFile);
   Image *noise=new Image(img->getWidth(),img->getHeight());
    srand(time(0));
    noise->generateNoiseImage();
    CompositeImage compo(*img,*noise,0.5);
    Histogram histo(compo);
    int t1 =  histo.getThreshold();
    Binarize b;
    Image binary_image = (b.image_binarize(compo,t1));
    ConnectedComponent newImg(binary_image);
    newImg.writePPM("output_task8_imt2016021.ppm");
    return;
}


int main(int argc, char **argv){

char arr[]={'1','3','5','6','7','8'};
cout<<"Our group task ID combination is: 1,3,5,6,7,8 "<<endl;
int a=sizeof(arr);
int i=0;char c;
while(i<a){
   c=arr[i];
      if(c=='1')
         PartE(argv[1]);
      else if(c=='3')
         PartA(argv[1]);
      else if(c=='5')
         PartB(argv[1]);
      else if(c=='6')
         PartC(argv[1]);
      else if(c=='7')
         PartD(argv[1]);
      else if(c=='8')
         PartF(argv[1]);
      i++;
   }
   cout<<"All Tasks Execution Completed"<<endl<<"Enter the task code to run Individual Task else enter 'e' to exit"<<endl;
   while(true){
      cin>>c;
         if(c=='1'){
            PartE(argv[1]);
         cout<<"Task Completed"<<endl;}
         else if(c=='3'){
            PartA(argv[1]);
            cout<<"Task Completed"<<endl;}
         else if(c=='5'){
            PartB(argv[1]);
            cout<<"Task Completed"<<endl;}
         else if(c=='6'){
            PartC(argv[1]);
            cout<<"Task Completed"<<endl;}
         else if(c=='7'){
            PartD(argv[1]);
            cout<<"Task Completed"<<endl;}
         else if(c=='8'){
            PartF(argv[1]);
            cout<<"Task Completed"<<endl;}
         else if(c=='e'){
               exit(0);
            }
         else
               cout<<"wrong key entered"<<endl;
      }
     return 0;
}
