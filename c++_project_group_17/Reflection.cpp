#include"Reflection.h"
#include"Image.h"

   Reflection::Reflection(){}
   Reflection::Reflection(Image I):Image(I){}

   Image Reflection::ReflectionX(){
      	Image answer(getWidth(),getHeight());
      	for(int i = 0 ; i < getHeight() ; i++){
      		for(int j = 0 ; j < getWidth() ; j++){
               Pixel p=getPixel(getHeight()-1-i,j);
      			answer.setPixel(i,j,p);
      		}
      	}
      	return answer;
      }


   Image Reflection::ReflectionY(){
      Image answer(getWidth(),getHeight());
      for(int i = 0 ; i < getHeight() ; i++){
         for(int j = 0 ; j < getWidth() ; j++){
            Pixel p=getPixel(i,getWidth()-1-j);
            answer.setPixel(i,j,p);
         }
      }
      return answer;
   }

   Image Reflection::ReflectionXY(){
      Image answer;
      answer=ReflectionX();
      Reflection ref=answer;
      answer=ref.ReflectionY();
      return answer;
   }
