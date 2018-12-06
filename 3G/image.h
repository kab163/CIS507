#include <stdio.h>
#pragma once

class Pixel
{
/* data members go here */
  public:
    unsigned char R;
    unsigned char G;
    unsigned char B;
  
    Pixel() {R = 0; G = 0; B = 0; };
    Pixel(unsigned char r, unsigned char g, unsigned char b) {R = r; G = g; B = b; };
} ;

class Image
{
/* data members go here */
  public:
    Pixel *data;
    int width;
    int height;

    Image() {width = 0; height = 0; data = NULL; };
    Image(int w, int h) {width = w; height = h; }; //malloc data

    void ResetSize(int width, int height);
} ;
