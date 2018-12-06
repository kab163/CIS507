#ifndef SINK_H
#define SINK_H

#include <image.h>
#include <sink.h>

class PNMwriter : public Sink 
{
  public:
    PNMwriter();
    void SetInput(Image img) {this->img = img; };
    void Write(char* filename);

  private:
    Image img;
};

#endif
/*end of file*/
