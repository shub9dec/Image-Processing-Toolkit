#include <iostream>
#include "Color.h"
#include "Pixel.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "Image.h"
using namespace std;


    Image::Image()
    {

    }

    Image::Image(int wid, int hei): _width(wid), _height(hei){

        _image = new Pixel*[_height];
        for(int i = 0; i < _height; i++){
            _image[i] = new Pixel[_width];
        }

    }
    void Image::setPixel(int x,int y,Pixel P){
      _image[x][y]=P;
      _image[x][y].setX(x);
      _image[x][y].setY(y);

   }
   void Image::setColorOfPixel(int x,int y,Color C){
            _image[x][y].setColor(C);
   }

   Pixel Image::getPixel(int x,int y){
      return _image[x][y];
   }

   int Image::getHeight(){
      return _height;
   }
   int Image::getWidth(){
      return _width;
   }


    void Image::generateNoiseImage(){
        for(int i = 0 ; i < _height ; i++){
            for(int j = 0 ; j < _width ; j++){
                int random = rand()%256;
                Color c(random, random, random);
                _image[i][j].setColor(c);
                _image[i][j].setX(i+1);
                _image[i][j].setY(j+1);
            }
        }
    }

    Image::Image(const Image &I):
            _width(I._width), _height(I._height) {
        _image = new Pixel*[_height];
        for(int i = 0; i < _height; ++i)
            _image[i] = new Pixel[_width];

        for(int i = 0 ; i < _height ; i++){
            for(int j = 0 ; j < _width ; j++){
                _image[i][j] = I._image[i][j];
            }
        }
    }

    void Image::readPPM(const string &inputFile){

        ifstream in(inputFile);
        string hash, dummy;
        if(!in){cout<<"unable to open file";exit(0);}
        while(1){
            in >> dummy;
            if(dummy[0] == '#')
                getline(in,dummy);
            else{
                hash = dummy;
                break;
            }
        }
        if(hash == "P3"){
            int width;
            while(1){
                in >> dummy;
                if(dummy[0] == '#')
                    getline(in,dummy);
                else{
                    width = stoi(dummy);
                    break;
                }
            }
            int height;
            while(1){
                in >> dummy;
                if(dummy[0] == '#')
                    getline(in,dummy);
                else{
                    height = stoi(dummy);
                    break;
                }
            }

            _width = width;
            _height = height;
            int maxPixelVal;
            while(1){
                in >> dummy;
                if(dummy[0] == '#')
                    getline(in,dummy);
                else{
                    maxPixelVal = stoi(dummy);
                    break;
                }
            }
            _image = new Pixel*[_height];
            for(int i = 0; i < _height; i++){
                _image[i] = new Pixel[_width];
            }
            for(int i = 0 ; i <_height ; i++){
                for(int j = 0 ; j < _width ; j++){
                    _image[i][j].setX(i+1);
                    _image[i][j].setY(j+1);
                    float r,g,b;
                    in >> r >> g >> b;

                    Color color(r, g, b);
                    _image[i][j].setColor(color);
                }
            }
        }

        else{
            cout << "This file format is not supported" << endl;
            exit(1);


        }

        in.close();

    }


    void Image::writePPM(const string &fileName){
        ofstream out(fileName);

        out << "P" << 3 << "\n";
        out << _width << " " << _height << "\n";
        float maxPixelVal =  0;
        for(int i = 0 ; i <_height ; i++){
                for(int j = 0 ; j < _width ; j++){
                    if(maxPixelVal < (_image[i][j]).getColor().getRed()){
                        maxPixelVal = (_image[i][j]).getColor().getRed();
                    }
                    if(maxPixelVal < (_image[i][j]).getColor().getGreen()){
                        maxPixelVal = (_image[i][j]).getColor().getGreen();
                    }
                    if(maxPixelVal < (_image[i][j]).getColor().getBlue()){
                        maxPixelVal = (_image[i][j]).getColor().getBlue();
                    }

                }
            }
        if(maxPixelVal == 0)
            out << 1 << "\n";
        else
            out << (int)maxPixelVal << "\n";

        for(int i = 0 ; i <_height ; i++){
                for(int j = 0 ; j < _width ; j++){
                    out << (int)((_image[i][j]).getColor().getRed()) << " ";
                    out << (int)((_image[i][j]).getColor().getGreen()) << " ";
                    out << (int)((_image[i][j]).getColor().getBlue()) << " ";

                }

                out << "\n";
            }
        out.close();
    }

    void Image::applyFilter(const Color &c, float opacity){
        for(int i = 0 ; i <_height ; i++){
                for(int j = 0 ; j < _width ; j++){
                    _image[i][j].setColor((1-opacity)*_image[i][j].getColor()
                     + opacity*c);
                }
            }


    }

    Image::~Image(){
        for(int i = 0; i < _height; ++i)
            delete[] _image[i];
        delete[] _image;
    }

    void Image::operator=(const Image &I){

        _width = I._width;
        _height = I._height;

        _image = new Pixel*[_height];
        for(int i = 0; i < _height; ++i)
            _image[i] = new Pixel[_width];

        for(int i = 0 ; i < _height ; i++){
            for(int j = 0 ; j < _width ; j++){
                _image[i][j] = I._image[i][j];
            }
        }
    }

ostream& operator<<(ostream& os, const Image &I) {
    for(int i = 0 ; i < I._height ; i++){
        for(int j = 0 ; j < I._width-1 ; j++){
            os << I._image[i][j] << " ";
        }
        os << I._image[i][I._width-1] << endl;
    }
    return os;
}

Image operator +(const Image &i1, const Image &i2){
    Image answer(i1._width, i1._height);
    if(i1._height == i2._height && i1._width == i2._width){
        for(int i = 0 ; i < i1._height ; i++){
            for(int j = 0 ; j < i1._width ; j++){
                Color c(i1._image[i][j].getColor() + i2._image[i][j].getColor());
                answer._image[i][j].setColor(c);
                answer._image[i][j].setX(i+1);
                answer._image[i][j].setY(j+1);
            }
        }
        return answer;
    }
    else{
        cout << "Image size does not match for addition operation\n";
    }

}

Image operator *(const Image &i1, float alpha){
    Image answer(i1._width, i1._height);
    for(int i = 0 ; i < i1._height ; i++){
        for(int j = 0 ; j < i1._width ; j++){
            Color c((i1._image[i][j].getColor())*alpha);
            answer._image[i][j].setColor(c);
            answer._image[i][j].setX(i+1);
            answer._image[i][j].setY(j+1);
        }
    }
    return answer;
}

Image operator *(float alpha, const Image &i1){
    Image answer(i1._width, i1._height);
    for(int i = 0 ; i < i1._height ; i++){
        for(int j = 0 ; j < i1._width ; j++){
            Color c((i1._image[i][j].getColor())*alpha);
            answer._image[i][j].setColor(c);
            answer._image[i][j].setX(i+1);
            answer._image[i][j].setY(j+1);
        }
    }
    return answer;
}
