#pragma once
#include <image.h>

class Sink
{
  public:
    void SetInput(Image *_img) { img = _img; };
    void SetInput2(Image *_img2) { img2 = _img2; };
    Sink();
  protected:
    Image *img;
    Image *img2;
};

/*end of file*/
