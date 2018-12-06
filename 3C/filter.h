#ifndef FILTER_H
#define FILTER_H

#include <image.h>
#include <sink.h>
#include <source.h>

class Filter : public Sink, public Source
{
  public : 
    Image GetOutput();
    virtual void Execute() = 0;
    virtual void Update() = 0;
    void SetInput(Image _img) { this->img = _img; };
    void SetInput2(Image _img2) { this->img2 = _img2; }; 
  protected :
    Image output;
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

#endif
/*end of file*/
