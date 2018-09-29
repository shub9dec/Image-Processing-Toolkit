#include <iostream>
#include "Color.h"
using namespace std;

#ifndef PIXEL_H
#define PIXEL_H

class Pixel{
private:
    int _xlocation;
    int _ylocation;
    Color _color;

public:
    Pixel();

    Pixel(int x, int y, Color c);

    Pixel(const Pixel &p);

    void setX(int x);

    void setY(int y);

    int getX() const;

    int getY() const;

    void setColor(const Color &c);

    Color getColor() const;

    ~Pixel();



    void operator=(const Pixel &b);

    friend ostream& operator<<(ostream& os, const Pixel &p);
    friend istream& operator>>(istream& is, Pixel &p);


};
#endif