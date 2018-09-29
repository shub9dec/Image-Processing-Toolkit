#ifndef ScaledImage_H_
#define ScaledImage_H_

#include "Image.h"
#include "Reflection.h"
#include<vector>

using namespace std;
class ScaledImage :public Image{
   private:
      Image Main_Img;
      vector<Image> ref_images;

    public:
        ScaledImage();
        ScaledImage(Image I);
        ~ScaledImage();
        void CreateImages();
        void Compos();
        void run();
};
#endif
