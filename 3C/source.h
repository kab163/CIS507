#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>

class Source
{
  public:
    Image* GetOutput();

    virtual void Execute() = 0;
    virtual void Update() = 0;
    Source();

  protected:
    Image *img;
};

#endif
/*end of file*/
