#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <image.h>

void
ResetSize(int width, int height) 
{
  //this->width = width;
  //this->height = height;
  //this->data = *(Pixel*)malloc(width * height * sizeof(Pixel));
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
/*int 
GetPixelIndex(int width, int height, int row, int column)
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
}*/

#endif
