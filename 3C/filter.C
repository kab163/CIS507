#include <image.h>
#include <filter.h>
#include <assert.h>


void Filter::SetInput(Image _img) {this->img = _img; }

void Filter::SetInput2(Image _img) {this->img2 = _img; }

Image Filter::GetOutput() {return this->img; }

//void LRCombine::SetInput2(Image _img) {this->img2 = _img;}

//void TBCombine::SetInput2(Image _img) {this->img2 = _img;}

//void Blender::SetInput2(Image _img) {this->img2 = _img;}

void Blender::SetFactor(double _factor) {this->factor = _factor; }

void Shrinker::Execute() {
  img2.width = (img.width + 1) / 2;
  img2.height = (img.height + 1) / 2;

  img2.data = (Pixel*)malloc(3 * img2.width * img2.height * sizeof(Pixel));

  for(int i = 0; i < img2.height; i++) {
    for (int j = 0; j < img2.width; j++) {
      img2.data[i * img2.width + j] = img.data[(2*i) * img.width + (2*j)];
    }
  }
}

void LRCombine::Execute() {
  assert(img.width == img2.width);
  
  img3.width = 2 * img.width;
  img3.height = img.height;

  img3.data = (Pixel*)malloc(3 * img3.width * img3.height * sizeof(Pixel));

  for(int i = 0; i < img3.height; i++) {
    for(int j = 0; j < img3.width; j++) {
      if (j >= 0 && j < img.width) img3.data[i * img3.width + j] = img.data[i * img.width + j];
      else img3.data[i * img3.width + j] = img2.data[i * img2.width + (j - img2.width)];
    }
  }
}

void TBCombine::Execute() {
  assert(img.height == img2.height);

  img3.width = img2.width;
  img3.height = 2* img2.height;

  img3.data = (Pixel*)malloc(3 * img3.width * img3.height * sizeof(Pixel));

  for(int i = 0; i < img3.height; i++) {
    for(int j = 0; j < img3.width; j++) {
      if (i >= 0 && i < img2.height) img3.data[i * img3.width + j] = img2.data[i * img2.width + j];
      else img3.data[i * img3.width + j] = img.data[(i-img.height) * img.width + j];
    }
  }

}

void Blender::Execute() {
  assert(img.height == img2.height);
  assert(img.width == img2.width);

  img3.height = img.height;
  img3.width = img.width;

  img3.data = (Pixel*)malloc(3 * img3.height * img3.width * sizeof(Pixel));

  for (int i = 0; i < img3.height; i++) {
    for (int j = 0; j < img3.width; j++) {
      img3.data[i * img3.width + j].R = (this->factor * (img.data[i * img3.width + j].R)) + 
                                          ((1-this->factor) * (img2.data[i * img3.width + j].R));
      img3.data[i * img3.width + j].G = (this->factor * (img.data[i * img3.width + j].G)) + 
                                          ((1-this->factor) * (img2.data[i * img3.width + j].G));
      img3.data[i * img3.width + j].B = (this->factor * (img.data[i * img3.width + j].B)) + 
                                          ((1-this->factor) * (img2.data[i * img3.width + j].B));
    }
  }

}

/*end of file*/
