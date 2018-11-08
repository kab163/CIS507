//#ifndef FUNCTION_H
//#define FUNCTION_H

//#include <image.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <functions.h>

#define VAL 128

/*
 * Arguments:
 * Image *img: the image that is being written to
 * char *filename: the name of the input file to read from
 */
void
ReadImage(Image *img, char *filename)
{  
  FILE *f_in;
  f_in = fopen(filename, "rb");
  int w, h, m;
  char magicNum[VAL];
  fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &w, &h, &m);

  if (strncmp(magicNum, "P6", 2) != 0) {fprintf(stderr, "There is something wrong with input file!\n"); exit(EXIT_FAILURE); }
  if (m != 255) {fprintf(stderr, "There is something wrong with input file!\n"); exit(EXIT_FAILURE); }

  img->width = w;
  img->height = h;

  img->data = (Pixel*) malloc((img->width * img->height) * sizeof(Pixel));
  for (int i = 0; i < (img->width * img->height); i++) {
    img->data[i] = *(Pixel*) malloc(3*sizeof(unsigned char));
  }

  int y = 0; 
  while (fscanf(f_in, "%c", &img->data[y].R) == 1) {
    fscanf(f_in, "%c", &img->data[y].G);
    fscanf(f_in, "%c", &img->data[y].B);
    y++;
  }
}

/*
 * Arguments:
 * Image *img: the image whose data needs to be written
 * char *filename: the name of the output file to write to
 */
void 
WriteImage(Image *img, char *filename)
{
  FILE *f_out;
  f_out = fopen(filename, "wb");
  fprintf(f_out, "%s\n%d %d\n%d\n", "P6", img->width, img->height, 255);

  for (int y = 0; y < (img->width * img->height); y++) {
    fwrite(&img->data[y].R, sizeof(unsigned char), 1, f_out);
    fwrite(&img->data[y].G, sizeof(unsigned char), 1, f_out);
    fwrite(&img->data[y].B, sizeof(unsigned char), 1, f_out);
  }

  free(img->data);
}

/*
 * Arguments:
 * Image *input: pointer to input image that is to be modified by function
 */
void
YellowDiagonal(Image *input) //yellow is R/G/B = 255/255/0
{ 
  for (int i = 0; i < input->width; i++) { 
    for (int j = 0; j < input->height; j++) {
      if (i == j) { //pixel is on diagonal if i == j
        input->data[i * input->width + j].R = 255;
        input->data[i * input->width + j].G = 255;
        input->data[i * input->width + j].B = 0;
      }
    }
  }
}

/*
 * Arguments:
 * Image *input: pointer to input image that is to be modified by function
 * Image *output: pointer to output image that the modified image is written to
 */
void HalfSize(Image *input, Image *output) 
{ 
  output->width = (input->width + 1) / 2;
  output->height = (input->height + 1) / 2;

  output->data = (Pixel*)malloc(3 * output->width * output->height * sizeof(Pixel));

  for(int i = 0; i < output->height; i++) {
    for (int j = 0; j < output->width; j++) {
      output->data[i * output->width + j] = input->data[(2*i) * input->width + (2*j)];
    }
  }
}

/*
 * Arguments:
 * Image *leftInput: pointer to input image that is left half of image to be modified by function
 * Image *rightInput: pointer to input image that is right half of image to be modified by function
 * Image *output: pointer to output image that the modified image is written to
 */
void LeftRightCombine(Image *leftInput, Image *rightInput, Image *output) 
{ 
  assert(leftInput->width == rightInput->width);
  
  output->width = 2 * leftInput->width;
  output->height = leftInput->height;

  output->data = (Pixel*)malloc(3 * output->width * output->height * sizeof(Pixel));

  for(int i = 0; i < output->height; i++) {
    for(int j = 0; j < output->width; j++) {
      if (j >= 0 && j < leftInput->width) output->data[i * output->width + j] = leftInput->data[i * leftInput->width + j];
      else output->data[i * output->width + j] = rightInput->data[i * rightInput->width + (j - rightInput->width)];
    }
  }
}

/*
 * Arguments:
 * Image *topInput: pointer to input image that is top half of image to be modified by function
 * Image *bottomInput: pointer to input image that is bottom half of image to be modified by function
 * Image *output: pointer to output image that the modified image is written to
 */
void TopBottomCombine(Image *topInput, Image *bottomInput, Image *output) 
{
  assert(topInput->height == bottomInput->height);

  output->width = bottomInput->width;
  output->height = 2* bottomInput->height;

  output->data = (Pixel*)malloc(3 * output->width * output->height * sizeof(Pixel));

  for(int i = 0; i < output->height; i++) {
    for(int j = 0; j < output->width; j++) {
      if (i >= 0 && i < bottomInput->height) output->data[i * output->width + j] = bottomInput->data[i * bottomInput->width + j];
      else output->data[i * output->width + j] = topInput->data[(i-topInput->height) * topInput->width + j];
    }
  }


}

/*
 * Arguments:
 * Image *input1: pointer to 1st input image that is to be blended by function
 * Image *input2: pointer to 2st input image that is to be blended by function
 * double factor: the opacity of the 1st image, 100-factor is opacity of 2nd image
 * Image *output: pointer to output image that the modified image is written to
 */
void Blend(Image *input1, Image *input2, double factor, Image *output) 
{
  assert(input1->height == input2->height);
  assert(input1->width == input2 ->width);

  output->height = input1->height;
  output->width = input1->width;

  output->data = (Pixel*)malloc(3 * output->height * output->width * sizeof(Pixel));

  for (int i = 0; i < output->height; i++) {
    for (int j = 0; j < output->width; j++) {
      output->data[i * output->width + j].R = (factor * (input1->data[i * output->width + j].R)) + ((1-factor) * (input2->data[i * output->width + j].R));
      output->data[i * output->width + j].G = (factor * (input1->data[i * output->width + j].G)) + ((1-factor) * (input2->data[i * output->width + j].G));
      output->data[i * output->width + j].B = (factor * (input1->data[i * output->width + j].B)) + ((1-factor) * (input2->data[i * output->width + j].B));
    }
  }
 
} 

//#endif
/* end of file */

