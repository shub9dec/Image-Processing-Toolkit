#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include<sstream>

#include "Image.h"
#include "ScaledImage.h"
#include "Reflection.h"
#include "CompositeImage.h"


ScaledImage::ScaledImage(){}

ScaledImage::ScaledImage(Image C):Main_Img(C){}


ScaledImage::~ScaledImage(){}

void ScaledImage::CreateImages(){
      Image image=Main_Img;
      Image image1(image.getWidth(),image.getHeight());
      Image image2(image.getWidth(),image.getHeight());
      Image image3(image.getWidth(),image.getHeight());
      Image image4(image.getWidth(),image.getHeight());

      for(int i=0;i<image.getHeight();i++){
         for(int j=0;j<image.getWidth();j++){
             image1.setColorOfPixel(i,j,Color(0,0,0));
             image2.setColorOfPixel(i,j,Color(0,0,0));
             image3.setColorOfPixel(i,j,Color(0,0,0));
             image4.setColorOfPixel(i,j,Color(0,0,0));
         }
     }

     for(int i=0;i<image.getHeight();i+=2){
         for(int j=0;j<image.getWidth();j+=2){
           Pixel p=image.getPixel(i,j);
            image1.setColorOfPixel(i/2,j/2,Color(p.getColor().getRed(),p.getColor().getGreen(),p.getColor().getBlue()));
        }
    }
     Reflection ref1(image1);
     image2=ref1.ReflectionY();
     Reflection ref2(image2);
     image3=ref2.ReflectionX();
     Reflection ref3(image3);
     image4=ref3.ReflectionY();
     ref_images.push_back(image1);
     ref_images.push_back(image2);
     ref_images.push_back(image3);
     ref_images.push_back(image4);
}

void ScaledImage::Compos(){
   CompositeImage C1(ref_images[0],ref_images[1],0.5);
   CompositeImage C2(ref_images[2],ref_images[3],0.5);
    Image A=C1;
    Image B=C2;
    CompositeImage C3(A,B,0.5);
    Image image =C3;
     for(int i=0;i<image.getHeight();i++){
         for(int j=0;j<image.getWidth();j++){
            if(i<image.getHeight()/4 || i>(3*image.getHeight())/4 || j<image.getWidth()/4 || j>(3*image.getWidth())/4){
                  image.setColorOfPixel(i,j,Color(0,0,0));
            }
         }
     }
     image.writePPM("output_task7_imt2016111.ppm");
}

void ScaledImage::run(){
   CreateImages();
   Compos();
}
