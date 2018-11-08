//#include <image.h>
#include <functions.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if(argc != 3) {fprintf(stderr, "Usage: exe intput_file output_file\n\n"); exit(EXIT_FAILURE); }  

  Image img, img2, img3, img4, img5, img6, img7, img8;

  ReadImage(&img, argv[1]);
  HalfSize(&img, &img2);
  LeftRightCombine(&img2, &img2, &img3);
  TopBottomCombine(&img3, &img3, &img4);
  HalfSize(&img4, &img5);
  LeftRightCombine(&img5, &img2, &img6);
  TopBottomCombine(&img6, &img3, &img7);
  Blend(&img7, &img, 0.795, &img8);
  WriteImage(&img8, argv[2]);

  free(img.data);
  free(img2.data);
  free(img3.data);
  free(img4.data);
  free(img5.data);
  free(img6.data);
  free(img7.data);

  return 0;
}
