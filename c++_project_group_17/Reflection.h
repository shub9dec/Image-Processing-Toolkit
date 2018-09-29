
#ifndef Reflection_H_
#define Reflection_H_

#include"Image.h"


class Reflection:public Image{
public:
   Reflection();
   Reflection(Image I);

   Image ReflectionX();

   Image ReflectionY();
   Image ReflectionXY();

};

#endif
