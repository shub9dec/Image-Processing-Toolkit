#include <iostream>
#include "Pixel.h"
#include "Color.h"

using namespace std;


    Pixel::Pixel()
    {

    }

    Pixel::Pixel(int x, int y, Color c):
            _xlocation(x), _ylocation(y), _color(c)
    {

    }

    Pixel::Pixel(const Pixel &p):
            _xlocation(p._xlocation), _ylocation(p._ylocation), _color(p._color) {

    }

    void Pixel::setX(int x){
        _xlocation = x;
    }
    void Pixel::setY(int y){
        _ylocation = y;
    }
    int Pixel::getX() const{
        return _xlocation;
    }
    int Pixel::getY() const{
        return _ylocation;
    }
    void Pixel::setColor(const Color &c){
        _color = c;
    }
    Color Pixel::getColor() const {return _color;}

    Pixel::~Pixel(){

    }



    void Pixel::operator=(const Pixel &b){
        _xlocation = b._xlocation;
        _ylocation = b._ylocation;
        _color = b._color;
    }



ostream& operator<<(ostream& os, const Pixel &p) {
    os << p._color;
    return os;
}

istream& operator>>(istream& is, Pixel &p) {
    is >> p._xlocation >> p._ylocation >> p._color;
    return is;
}