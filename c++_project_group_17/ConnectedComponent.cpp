#include "ConnectedComponent.h"
#include<iostream>
#include <cmath>
#include<vector>
#include<set>
#include<algorithm>
#include "Color.h"
#include "Pixel.h"
#include "Image.h"

using namespace std;

void ConnectedComponent:: dfsVisit(int s){
  vis[s]=1;
  for(int i=0;i<equi_labels[s].size();i++){
    if(vis[equi_labels[s][i]]==0){
      labels[equi_labels[s][i]]=labels[s];
      dfsVisit(equi_labels[s][i]);
    }
  }
}

void ConnectedComponent:: dfs(){
  for(int i=1;i<equi_labels.size();i++){
    if(vis[i]==0){
      dfsVisit(i);
    }
  }
}

ConnectedComponent:: ConnectedComponent(){

}

ConnectedComponent:: ConnectedComponent(Image& img){
  black = new Color(0,0,0);
  _width = img.getWidth();
  _height = img.getHeight();
  _image = new Pixel*[_height];
  for(int i = 0; i < _height; i++)
  {
    _image[i] = new Pixel[_width];
  }
  matrix.resize(_height);
  for(int i=0;i<_height;i++){
    matrix[i].resize(_width);
  }
  for(int i=0;i<_height;i++){
    for(int j=0;j<_width;j++){
      if(img.getPixel(i,j).getColor()==*black){
        matrix[i][j]=1;
      }
      else{
        matrix[i][j]=0;
      }
    }
  }
  labels.push_back(0);
  vector<int> temp;
  equi_labels.push_back(temp);
  vis.push_back(0);

  for(int i=0;i<_height;i++){
    for(int j=0;j<_width;j++){
      if(matrix[i][j]==1){
        set<int> tempSet;
        if(i!=0){
          for(int x=-1;x<2;x++){
            if(j+x>=0 and j+x<_width and matrix[i-1][j+x]!=0){
              tempSet.insert(matrix[i-1][j+x]);
            }
          }
        }
        if(j!=0 and matrix[i][j-1]!=0){
          tempSet.insert(matrix[i][j-1]);
        }
        if(tempSet.size()==0){
          matrix[i][j] = labels.size();
          labels.push_back(matrix[i][j]);
          vector<int> temp;
          equi_labels.push_back(temp);
          vis.push_back(0);
        }
        else if(tempSet.size()==1){
          matrix[i][j] = *(tempSet.begin());
        }
        else{
          int minLabel = *(tempSet.begin());
          matrix[i][j] = minLabel;
          set<int>:: iterator itr = tempSet.begin();
          while(itr!=tempSet.end()){
            itr++;
            //equi_labels[*itr].push_back(minLabel);
            equi_labels[minLabel].push_back(*itr);
          }
        }
      }
    }
  }

  dfs();

  int r=0,g=0,b=0;
  Color * red = new Color(255,0,0);
  Color * green = new Color(0,255,0);
  Color * blue = new Color(0,0,255);
  Color * white = new Color(255,255,255);
  Color * yellow = new Color(255,255,0);
  colors.push_back(*black);
  colors.push_back(*red);
  colors.push_back(*green);
  colors.push_back(*blue);
  colors.push_back(*white);
  colors.push_back(*yellow);


  for(int i=0;i<_height;i++){
    for(int j=0;j<_width;j++){
      Pixel * tempPix = new Pixel(i,j,colors[labels[matrix[i][j]]%6]);
      setPixel(i,j,*tempPix);
      //cout << labels[matrix[i][j]] << endl;
    }
  }
}
