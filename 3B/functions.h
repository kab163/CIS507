#ifndef IMAGE_H
#define IMAGE_H

#include <image.h>

void ReadImage(Image *img, char *filename);
void WriteImage(Image *img, char *filename);

void YellowDiagonal(Image *input);
void HalfSize(Image *input, Image *output);
void LeftRightCombine(Image *leftInput, Image *rightinput, Image *output);
void TopBottomCombine(Image *topInput, Image *bottomInput, Image *output);
void Blend(Image *input1, Image *input2, double factor, Image *output);

#endif
