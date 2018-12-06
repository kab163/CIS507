#include <stdio.h>
#pragma once

class Source;

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
    Source *source;
    Pixel *data;
    int width;
    int height;

    Image() {width = 0; height = 0; data = NULL; source = NULL; };
    Image(int w, int h, Pixel *d) {width = w; height = h; data = d; }; //malloc data
    Image(const Image &i) {height = i.height; width = i.width; data = i.data; };

    void SetSource(Source *s)    {source = s; };
    void ResetSize(int w, int h) { width = w; height = h; };
    void SetData(Pixel *d)       { data = d; };
    void Update() const;
    int GetWidth() const         { return width; };
    int GetHeight() const        { return height; };
    Pixel *GetData() const        { return data; };
} ;
