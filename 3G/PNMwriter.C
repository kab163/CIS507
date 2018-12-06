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
  fprintf(f_out, "%s\n%d %d\n%d\n", "P6", img.width, img.height, 255);

  for (int y = 0; y < (img.width * img.height); y++) {
    fwrite(&img.data[y].R, sizeof(unsigned char), 1, f_out);
    fwrite(&img.data[y].G, sizeof(unsigned char), 1, f_out);
    fwrite(&img.data[y].B, sizeof(unsigned char), 1, f_out);
  }

  free(img.data);
}

/*end of file*/
