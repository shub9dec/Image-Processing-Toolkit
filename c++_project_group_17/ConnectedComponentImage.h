#ifndef TASK6_H
#define TASK6_H

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
using namespace std;

class ConnectedComponentImage{
private:
  void getPixelCount(const Image& i , int *PixelCount);

  double getMedianThreshold(int *PixelCount);

  Image BinaryImage(const Image& i , double MedianThreshold);

  void Matrix_for_BFS(const Image& i , int **a);

  void BFS(const Image& i , int **a , int row , int col , bool **visited , Color* , int count);

  void WhiteComponents(const Image& i , int **a , bool **visited , Color*);
public:
  ConnectedComponentImage();
  ~ConnectedComponentImage();
  ConnectedComponentImage(const ConnectedComponentImage& T);
  void Run6(string);
};

#endif
