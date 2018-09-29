#include <iostream>
#include "Color.h"

using namespace std;

	Color::Color(float r, float g, float b):
        _red(r), _green(g), _blue(b)
    {

    }

    Color::Color(const Color &c):
            _red(c._red), _green(c._green), _blue(c._blue) {

    }
    Color::~Color(){

    }
	 
    float Color::getRed() const{return _red;}
    float Color::getGreen() const{return _green;}
    float Color::getBlue() const{return _blue;}

    void Color::setRed(float c){_red = c;}
    void Color::setGreen(float c){_blue = c;}
    void Color::setBlue(float c){_green = c;}

    void Color::operator=(const Color &b){
        _red = b._red;
        _green = b._green;
        _blue = b._blue;
    }

    ostream& operator<<(ostream& os, const Color &c) {
		 os<<c._red<<" "<<c._green<<" "<<c._blue;
}

istream& operator>>(istream& is, Color &c) {
    is >> c._red >> c._green >> c._blue;
    return is;
}

Color operator+ (const Color &c1, const Color &c2){
    Color answer(c1._red + c2._red, c1._green + c2._green, c1._blue + c2._blue);
    return answer;
}
Color operator* (const float &f, const Color &c2){
    Color answer(f*c2._red, f*c2._green, f*c2._blue);
    return answer;
}

Color operator* (const Color &c2, const float &f){
    Color answer(f*c2._red, f*c2._green, f*c2._blue);
    return answer;
}

bool operator==(const Color &c1, const Color &c2){
    return (c1._red == c2._red && c1._green == c2._green && c1._blue == c2._blue);
}
