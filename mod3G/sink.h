#ifndef SINK_H
#define SINK_H

#include <image.h>

class Sink
{
  public:
    void SetInput(const Image *_img1) { img1 = _img1; };
    void SetInput2(const Image *_img2) { img2 = _img2; };
    Sink();
  protected:
    const Image *img1;
    const Image *img2;
};

class CheckSum : public Sink
{
  public:
    void OutputCheckSum(const char *filename);

  protected:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    const char * filename;

};

#endif
/*end of file*/
