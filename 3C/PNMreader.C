#include <image.h>
#include <PNMreader.h>
#include <source.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAL 128

PNMreader::PNMreader(char* _filename) {
  this->filename = _filename;
}

/*
Image PNMreader::GetOutput() {
  return this->img; 
}
*/

void PNMreader::Execute() {
  FILE *f_in;
  f_in = fopen(filename, "rb");
  if(f_in == NULL) exit(EXIT_FAILURE);   

  int w, h, m;
  char magicNum[VAL];
  fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &w, &h, &m);

  if (strncmp(magicNum, "P6", 2) != 0) {fprintf(stderr, "There is something wrong with input file!\n"); exit(EXIT_FAILURE); }
  if (m != 255) {fprintf(stderr, "There is something wrong with input file!\n"); exit(EXIT_FAILURE); }

  img.height = h;
  img.width = w;  

  img.data = (Pixel*) malloc((img.width * img.height) * sizeof(Pixel));
  for (int i = 0; i < (img.width * img.height); i++) {
    img.data[i] = *(Pixel*) malloc(3*sizeof(unsigned char));
  }

  int y = 0; 
  while (fscanf(f_in, "%c", &img.data[y].R) == 1) {
    fscanf(f_in, "%c", &img.data[y].G);
    fscanf(f_in, "%c", &img.data[y].B);
    y++;
  }

}

/*end of file*/
