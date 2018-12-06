#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <image.h>
#include <source.h>

void Image::Update() const {
  if (source != NULL) source->Update();
}

#endif
