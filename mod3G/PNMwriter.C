#include <sink.h>
#include <PNMwriter.h>
#include <image.h>
#include <stdio.h>
#include <stdlib.h>

PNMwriter::PNMwriter () {
  //what should go here?
}

void PNMwriter::Write (char* filename) {
  FILE *f_out;
  f_out = fopen(filename, "wb");
  fprintf(f_out, "%s\n%d %d\n%d\n", "P6", img1->GetWidth(), img1->GetHeight(), 255);

  //this is easier way...
  fwrite(img1->GetData(), sizeof(Pixel), img1->GetWidth() * img1->GetHeight(), f_out);

/*
  for (int y = 0; y < (img1->width * img1->height); y++) {
    fwrite(&img1->data[y].R, sizeof(unsigned char), 1, f_out);
    fwrite(&img1->data[y].G, sizeof(unsigned char), 1, f_out);
    fwrite(&img1->data[y].B, sizeof(unsigned char), 1, f_out);
  }
*/
  fclose(f_out);
  //free(img.data);
}

/*end of file*/
