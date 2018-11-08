#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAL 128

typedef struct
{
/* data members go here */
  unsigned char R;
  unsigned char G;
  unsigned char B;
} Pixel;

typedef struct
{
/* data members go here */
  Pixel *data;
  int width;
  int height;
} Image;

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

  img->data = malloc((img->width * img->height) * sizeof(Pixel));
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

void WriteImage(Image *img, char *filename)
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
 *    width:  the width of the image
 *    height: the height of the image
 *    row:    the row of the pixel
 *    column: the column of the pixel
 *
 * Returns: the index of the pixel in the image for (column, row)
 */

int GetPixelIndex(int width, int height, int row, int column)
{
    if (column < 0 || column >= width)
    {
        fprintf(stderr, "You asked for a pixel index for column %d, but the only valid values are between 0 and %d\n", column, width-1);
        exit(EXIT_FAILURE);
    }
    if (row < 0 || row >= height)
    {
        fprintf(stderr, "You asked for a pixel index for row %d, but the only valid values are between 0 and %d\n", row, height-1);
        exit(EXIT_FAILURE);
    }
    return row*width + column;
}

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

int main(int argc, char *argv[])
{
	/* Read an image, apply yellow diagonal to it, then write */
	if (argc != 3) fprintf(stderr, "Usage: exe input_file output_file");

	Image picture;
	ReadImage(&picture, argv[1]);
	YellowDiagonal(&picture);
	WriteImage(&picture, argv[2]);

	return 0;
}

