#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <image.h>

class Filter
{
  public:
    void SetInput2(Image img);
    void SetInput(Image img);
    Image GetOutput();
    Image img;
    //Image img2;

};

class Shrinker : public Filter
{
  public:
    void Execute();

  private:
    Image img2;

};

class LRCombine : public Filter
{
  public:
  
    void Execute();
  
  private:
    Image img2;
    Image img3;  

};

class TBCombine : public Filter
{
  public: 
    void Execute();

  private:
    Image img2;
    Image img3;

};

class Blender : public Filter
{
  public:
   
    void SetFactor(double factor);
    void Execute();

  private:
    Image img2;
    Image img3;
    double factor;

};

#endif
/*end of file*/
