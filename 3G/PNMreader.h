#ifndef SOURCE_H
#define SOURCE_H
#include <source.h>

class PNMreader : public Source
{
  public: 
    PNMreader(char * filename);
    Image GetOutput();
    void Execute();

  private:
    char* filename;
    Image img; 
 
};

#endif
/*end of file*/
