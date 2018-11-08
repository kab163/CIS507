#include <stdio.h>
//#ifndef IMAGE_H
//#define IMAGE_H

struct Pixel
{
/* data members go here */
  unsigned char R;
  unsigned char G;
  unsigned char B;
  
  //Pixel() {R = 0; G = 0; B = 0; };
  //Pixel(unsigned char r, unsigned char g, unsigned char b) {R = r; G = g; B = b; };
  //Pixel(const Pixel &p1) {R = p1.R; G = p1.G; B = p1.B; };
} ;

struct Image
{
/* data members go here */
  Pixel *data;
  int width;
  int height;

  //Image() {width = 0; height = 0; data = NULL; };
  //Image(int w, int h) {width = w; height = h; }; //malloc data
  //Image(const Image &i1) {width = i1.width; height = i1.height; }; //malloc data

  //int GetPixelIndex(int width, int height, int row, int col);
  //void ResetSize(int width, int height);
} ;

//#endif
