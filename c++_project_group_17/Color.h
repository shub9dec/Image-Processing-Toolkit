#include <iostream>
using namespace std;

#ifndef COLOR_H
#define COLOR_H
class Color{
private:
    float _red;
    float _green;
    float _blue;

public:
    Color(float r = 0, float g =0, float b = 0);

    Color(const Color &c);

    ~Color();

    float getRed() const;
    float getGreen() const;
    float getBlue() const;

    void setRed(float c);
    void setGreen(float c);
    void setBlue(float c);

    void operator=(const Color &b);

    friend ostream& operator<<(ostream& os, const Color &c);
    friend istream& operator>>(istream& is, Color &c);

    friend Color operator+ (const Color &c1, const Color &c2);
    friend Color operator* (const float &f, const Color &c2);
    friend Color operator* (const Color &c2, const float &f);
    friend bool operator==(const Color &c1, const Color &c2);
};
#endif