#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>

class Source
{
  public:
    Image* GetOutput();

    virtual void Execute() = 0;
    virtual void Update();
    Source();

  protected:
    Image img;
};

class Color : public Source {
  public:
    Color();
    Color(int w, int h, unsigned char _r, unsigned char _g, unsigned char _b);
    virtual void Execute();

  protected:
    int width;
    int height;
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

#endif
/*end of file*/
