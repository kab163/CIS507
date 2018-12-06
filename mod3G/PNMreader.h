#ifndef PNMREADER_H
#define PNMREADER_H

#include <source.h>

class PNMreader : public Source
{
  public: 
    PNMreader(char * filename); 
    //Image GetOutput();
    virtual void Execute();

  protected:
    char* filename;
 
};

#endif
/*end of file*/
