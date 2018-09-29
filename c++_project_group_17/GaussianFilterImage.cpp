#include "Image.h"
#include "GaussianFilterImage.h"
#include <algorithm>
#include "Reflection.h"
#include "CompositeImage.h"

GaussianFilterImage::GaussianFilterImage(){

}
GaussianFilterImage::GaussianFilterImage(const GaussianFilterImage &t){

}
GaussianFilterImage::~GaussianFilterImage(){

}

Color GaussianFilterImage::RgbToHsvUtil(const Color &c){
	float r = c.getRed();
	float g = c.getGreen();
	float b = c.getBlue();

	r/=255;
	g/=255;
	b/=255;

    double cMin, cMax, delta;

    float h, s, v;

    cMin = min(r, min(g,b));

    cMax = max(r,max(g,b));

    v = cMax;
    delta = cMax - cMin;
    if (delta < 0.00001)
    {
        s = 0;
        h = 0;
        return Color(h,s,v);
    }
    if( cMax > 0.0 ) {
        s = (delta / cMax);
    }
    else {
        s = 0.0;
        h = NAN;
        return Color(h,s,v);
    }
    if( r >= cMax )
        h = ( g - b ) / delta;
    else if( g >= cMax )
        h = 2.0 + ( b - r ) / delta;
    else
        h = 4.0 + ( r - g ) / delta;

    h *= 60.0;

    if( h < 0.0 )
        h += 360.0;

    return Color(h,s,v);

}
Image GaussianFilterImage::convertRgbToHsv(const Image &input){
	Image answer = input;
	for(int i = 0 ; i < answer._height ; i++){
		for(int j = 0 ; j < answer._width ; j++){
			Color temp = answer._image[i][j].getColor();
			answer._image[i][j].setColor(RgbToHsvUtil(temp));
		}
	}
	return answer;
}
void GaussianFilterImage::colour24Neighborhood(Image &input, const Color &c, int i, int j){
	for(int p = i-2 ; p <= i+2 ; p++){
		if(p < 0)
			continue;
		if(p >= input._height)
			break;
		for(int q = j-2 ; q <= j+2 ; q++){
			if(q < 0)
				continue;
			if(q >= input._width)
				break;
			input._image[p][q].setColor(c);
		}
	}
}
bool GaussianFilterImage::isLocalMaxima(const Image &input, int i, int j){
	for(int p = i-1 ; p <= i+1 ; p++){
		if(p < 0)
			continue;
		if(p >= input._height)
			break;
		for(int q = j - 1; q <= j+1 ; q++){
			if(q < 0)
				continue;
			if(q >= input._width)
				break;
			if(input._image[p][q].getColor().getGreen() > input._image[i][j].getColor().getGreen())
				return false;
		}
	}
	return true;
}
Image GaussianFilterImage::makeC(const Image &input){
	Image C(input._width, input._height);
	Color black(0,0,0), white(255,255,255);
	for(int i = 0 ; i < C._height ; i++){
		for(int j = 0 ; j < C._width ; j++){
			C._image[i][j].setColor(black);
			C._image[i][j].setX(i+1);
			C._image[i][j].setY(j+1);
		}
	}
	for(int i = 0 ; i < input._height ; i++){
		for(int j = 0 ; j < input._width ; j++){
			if(isLocalMaxima(input, i , j)){
				colour24Neighborhood(C, white, i, j);
			}
		}
	}

	return C;
}

void GaussianFilterImage::applyGaussianFilter(Image &c, const Image &input){
	int gaussianReference[][5] = {{1,4,7,4,1},
								{4,16,26,16,4},
								{7,26,41,26,7},
								{4,16,26,16,4},
								{1,4,7,4,1}};

	pair<int,int> gaussianMap[input._height][input._width]; //<gaussianValue,count>
	for(int i = 0 ; i < input._height ; i++){
		for(int j = 0 ; j < input._width ; j++){
			gaussianMap[i][j].first = 0;
			gaussianMap[i][j].second = 0;
		}
	}
	for(int i = 0 ; i < input._height ; i++){
		for(int j = 0 ; j < input._width ; j++){
			if(isLocalMaxima(input, i , j)){
				for(int p = i-2 ; p <= i+2 ; p++){
					if(p < 0)
						continue;
					if(p >= input._height)
						break;
					for(int q = j-2 ; q <= j+2 ; q++){
						if(q < 0)
							continue;
						if(q >= input._width)
							break;
						gaussianMap[p][q].first+=(gaussianReference[p-(i-2)][q-(j-2)]);
						gaussianMap[p][q].second+=1;
					}
				}
			}
		}
	}

	for(int i = 0 ; i < input._height ; i++){
		for(int j = 0 ; j < input._width ; j++){
			if(gaussianMap[i][j].second != 0){
				float temp = c._image[i][j].getColor().getRed();
				float colorVal = (temp*(gaussianMap[i][j].first))/(gaussianMap[i][j].second * 273);
				c._image[i][j].setColor(Color(colorVal,colorVal,colorVal));
			}
		}
	}

	return;

}


void GaussianFilterImage::run(const char* input){
	Image img;
	img.readPPM(input);
	Reflection ref(img);
	Image reflectedImage = ref.ReflectionX();
	// reflectedImage.writePPM("test.ppm");
	Image hsvReflectedImage = convertRgbToHsv(reflectedImage);
	Image C = makeC(img);
	applyGaussianFilter(C,hsvReflectedImage);
	CompositeImage answer(C,reflectedImage,0.6);
	answer.writePPM("output_task3_imt201670.ppm");
	return;

}
