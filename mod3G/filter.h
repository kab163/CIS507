#ifndef FILTER_H
#define FILTER_H

#include <image.h>
#include <sink.h>
#include <source.h>

class Filter : public Sink, public Source
{
  public : 
    //Image GetOutput();
    //virtual void Execute() = 0;
    virtual void Update();
    //void SetInput(Image* _img) { img = _img; };
    //void SetInput2(Image* _img2) { img2 = _img2; }; 
  protected :
    Image *output;
};

class Shrinker : public Filter
{
public:
  void Execute() override;
};

class LRCombine : public Filter
{
public:
  void Execute() override;
};

class TBCombine : public Filter
{
public:
  void Execute() override;
};

class Blender : public Filter
{
public:
  void Execute() override;
  void SetFactor(double factor);

private:
  double factor;
};

class Mirror : public Filter
{
  public:
    void Execute() override;
};

class Rotate: public Filter
{
  public:
    void Execute() override;
};

class Subtract: public Filter
{
  public:
    void Execute() override;
};

class Grayscale: public Filter
{
  public:
    void Execute() override;
};

class Blur: public Filter
{
  public:
    void Execute() override;
};


#endif
/*end of file*/
