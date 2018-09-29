#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <deque>
#include <locale>
#include <utility>
#include <stack>
#include <string>
#include <limits>
#include <cstdio>
#include <queue>
#include <bitset>
#include <cmath>
#include <set>
#define max(x, y) ((x)>(y)?(x):(y))
#define min(x, y) ((x)<(y)?(x):(y))

#include "Image.h"
#include "Pixel.h"
#include "Color.h"
#include "ConnectedComponentImage.h"

using namespace std;

ConnectedComponentImage::ConnectedComponentImage(){

}

ConnectedComponentImage::~ConnectedComponentImage(){

}

ConnectedComponentImage::ConnectedComponentImage(const ConnectedComponentImage& T){

}

// #####################################################  BINARY IMAGE Implementation   ####################################################

void ConnectedComponentImage::getPixelCount(const Image& input , int *PixelCount){
  for(int i = 0 ; i < input._height ; i++){
    for(int j = 0 ; j < input._width ; j++){
      for(int k = 0 ; k < 256 ; k++){
        int Brightness = (input._image[i][j].getColor().getRed() + input._image[i][j].getColor().getGreen() + input._image[i][j].getColor().getBlue())/3;
        if(Brightness == k)
          PixelCount[k]++;
      }
    }
  }
}

/* Median Threshold function is below : */

double ConnectedComponentImage::getMedianThreshold(int *PixelCount){
  long int cumulativeFrequency[256];
  long int sum = PixelCount[0];
  cumulativeFrequency[0] = PixelCount[0];
  for(int i = 1 ; i < 256 ; i++)
    {
      cumulativeFrequency[i] = cumulativeFrequency[i - 1] + PixelCount[i];
      sum += PixelCount[i];
    }
  int i = 0;
  if(sum % 2 == 0)
  {
    int index = sum / 2;
    while(index > cumulativeFrequency[i])
    {
      i++;
    }
    if(index + 1 > cumulativeFrequency[i])
    {
      return (i + (i + 1)) / 2.0;
    }
    else
    {
      return i;
    }
  }
  else
  {
    int index = (sum + 1) / 2;
    while(index > cumulativeFrequency[i])
    {
      i++;
    }
    return i;
  }
}

Image ConnectedComponentImage::BinaryImage(const Image& input , double MedianThreshold){
  Image answer = input;
  for(int i = 0 ; i < input._height ; i++){
    for(int j = 0 ; j < input._width ; j++){
      int Brightness = (input._image[i][j].getColor().getRed() + input._image[i][j].getColor().getGreen() + input._image[i][j].getColor().getBlue())/3;
      if(Brightness >= MedianThreshold){
        answer._image[i][j].setColor(Color(255 , 255 , 255));
      }
      else{
        answer._image[i][j].setColor(Color(0 , 0 , 0));
      }
    }
  }
  return answer;
}

// ##############################################   BFS Implementtion   #############################################################

void ConnectedComponentImage::Matrix_for_BFS(const Image& input , int **a){
  for(int i = 0 ; i < input._height ; i++){
    for(int j = 0 ; j < input._width ; j++){
      if(input._image[i][j].getColor() == Color(255 , 255 , 255)){
        a[i][j] = 1;
      }
      else{
        a[i][j] = 0;
      }
    }
  }
}

void ConnectedComponentImage::BFS(const Image& input , int **a , int row , int col , bool **visited , Color* Labels , int count){
  deque< pair<int, int> > q;
  q.push_back(make_pair(row, col));
  visited[row][col] = true;

  while(!q.empty()){
    pair<int, int> temp = q.front();
    q.pop_front();
    row = temp.first;
    col = temp.second;

    input._image[row][col].setColor(Labels[count%6]);

    for(int r = row-1 ; r < row+2 ; r++){
      for(int c = col-1 ; c < col+2 ; c++){
        if(r > 0 && c > 0 && r < input._height && c < input._width && (!visited[r][c]) && a[r][c] == 1){
          q.push_back(make_pair(r, c));
          visited[r][c] = true;
        }
      }
    }
  }
}

void ConnectedComponentImage::WhiteComponents(const Image& input , int **a , bool **visited , Color* Labels){
  int count = 0;
  for(int i = 0 ; i < input._height ; i++)
  {
    for(int j = 0 ; j < input._width ; j++)
    {
      if(a[i][j] && !visited[i][j])
      {
        BFS(input , a , i , j , visited , Labels , count);
        count++;

      }
    }
  }
}

/* Code Run */

void ConnectedComponentImage::Run6(string input){
  Image img;
	img.readPPM(input);

// ##########################################    BINARY IMAGE    ##########################################################################

  int PixelCount[256] = {0};
  getPixelCount(img , PixelCount);
  double MedianThreshold = getMedianThreshold(PixelCount);
  Image Binaryimg = BinaryImage(img , MedianThreshold);
  Binaryimg.writePPM("output_task6_imt2016130_binary.ppm");

// ################################################    Connected Components    ############################################################
  Color label[6] = {Color(0 , 255 , 255) , Color(255 , 0 , 255) , Color(255 , 255 , 0) , Color(0 , 0 , 255) , Color(255 , 0 , 0) , Color(0 , 255 , 0)};
  int **M;
  bool **visited;
  M = new int*[Binaryimg._height];
  for(int i = 0 ; i < Binaryimg._height ; i++)
  {
    M[i] = new int[Binaryimg._width];
  }
  visited = new bool*[Binaryimg._height]();
  for(int i = 0 ; i < Binaryimg._height ; i++)
  {
    visited[i] = new bool[Binaryimg._width];
    for(int j = 0; j < img._width; j++)   visited[i][j] = false;
  }

  Matrix_for_BFS(Binaryimg , M);
  WhiteComponents(Binaryimg , M , visited , label);
  Binaryimg.writePPM("output_task6_imt2016130_final.ppm");
}
