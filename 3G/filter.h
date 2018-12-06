#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <image.h>

class Filter
{
public :
    void SetInput(Image img);
    Image GetOutput();
    virtual void Execute() = 0;
protected :
    Image output;
    Image img;
};

class Filter2 : public Filter
{
  public :
    void SetInput2(Image img);
  protected :
    Image img2;
};

class Shrinker : public Filter
{
  public:
    void Execute() override;
};

class LRCombine : public Filter2
{
  public:
    void Execute() override;
};

class TBCombine : public Filter2
{
  public:
    void Execute() override;
};

class Blender : public Filter2
{
  public:
    void Execute() override;
    void SetFactor(double factor);

  private:
    double factor;
};

class Mirror : public Filter2
{
  public:
    void Execute() override;
};

class Rotate: public Filter2
{
  public:
    void Execute() override;
};

class Subtract: public Filter2
{
  public:
    void Execute() override;
};

class Grayscale: public Filter2
{ 
  public:
    void Execute() override;
};

class Blur: public Filter2
{ 
  public:
    void Execute() override;
};

#endif
/*end of file*/
