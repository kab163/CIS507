#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <image.h>

void
Image::ResetSize(int width, int height) 
{
  this->width = width;
  this->height = height;
  this->data = (Pixel*)malloc(width * height * sizeof(Pixel));
}

#endif
