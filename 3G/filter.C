#include <image.h>
#include <filter.h>
#include <assert.h>
#include <stdlib.h>

void Filter::SetInput(Image _img) {this->img = _img; }

void Filter2::SetInput2(Image _img) {this->img2 = _img; }

Image Filter::GetOutput() {return this->output; }

void Blender::SetFactor(double _factor) {this->factor = _factor; }

void Shrinker::Execute()
{
  this->output.width = (this->img.width + 1) / 2;
  this->output.height = (this->img.height + 1) / 2;

  this->output.data = (Pixel*)malloc(3 * this->output.width * this->output.height * sizeof(Pixel));

  for(int i = 0; i < this->output.height; i++) {
    for (int j = 0; j < this->output.width; j++) {
      this->output.data[i * this->output.width + j] = this->img.data[(2*i) * this->img.width + (2*j)];
    }
  }
}

void LRCombine::Execute() {
  assert(this->img.width == this->img2.width);
  
  this->output.width = 2 * this->img.width;
  this->output.height = this->img.height;

  this->output.data = (Pixel*)malloc(3 * this->output.width * this->output.height * sizeof(Pixel));

  for(int i = 0; i < this->output.height; i++) {
    for(int j = 0; j < this->output.width; j++) {
      if (j >= 0 && j < this->img.width) this->output.data[i * this->output.width + j] = this->img.data[i * this->img.width + j];
      else this->output.data[i * this->output.width + j] = this->img2.data[i * this->img2.width + (j - this->img2.width)];
    }
  }
}

void TBCombine::Execute() {
  assert(this->img.height == this->img2.height);

  this->output.width = this->img2.width;
  this->output.height = 2* this->img2.height;

  this->output.data = (Pixel*)malloc(3 * this->output.width * this->output.height * sizeof(Pixel));

  for(int i = 0; i < this->output.height; i++) {
    for(int j = 0; j < this->output.width; j++) {
      if (i >= 0 && i < this->img2.height) this->output.data[i * this->output.width + j] = this->img2.data[i * this->img2.width + j];
      else this->output.data[i * this->output.width + j] = this->img.data[(i-this->img.height) * this->img.width + j];
    }
  }

}

void Blender::Execute() {
  assert(this->img.height == this->img2.height);
  assert(this->img.width == this->img2.width);

  this->output.height = this->img.height;
  this->output.width = this->img.width;

  this->output.data = (Pixel*)malloc(3 * this->output.height * this->output.width * sizeof(Pixel));

  for (int i = 0; i < this->output.height; i++) {
    for (int j = 0; j < this->output.width; j++) {
      this->output.data[i * this->output.width + j].R = (this->factor * (this->img.data[i * this->output.width + j].R)) + 
                                          ((1-this->factor) * (this->img2.data[i * this->output.width + j].R));
      this->output.data[i * this->output.width + j].G = (this->factor * (this->img.data[i * this->output.width + j].G)) + 
                                          ((1-this->factor) * (this->img2.data[i * this->output.width + j].G));
      this->output.data[i * this->output.width + j].B = (this->factor * (this->img.data[i * this->output.width + j].B)) + 
                                          ((1-this->factor) * (this->img2.data[i * this->output.width + j].B));
    }
  }

}

void Mirror::Execute() {
  this->output.height = this->img.height;
  this->output.width = this->img.width;

  this->output.data = (Pixel*)malloc(3 * this->output.height * this->output.width * sizeof(Pixel));

  
  for (int i = 0; i < this->output.height; i++) {
    for (int j = 0; j < this->output.width; j++) {
      
    }
  } 
}

void Rotate::Execute() {
  this->output.height = this->img.height;
  this->output.width = this->img.width;

  this->output->data = (Pixel*)malloc(3 * this->output.height * this->output.width * sizeof(Pixel));

  
  for (int i = 0; i < this->output.height; i++) {
    for (int j = 0; j < this->output.width; j++) {
      
    }
  }
}

void Subtract::Execute() {
  this->output.height = this->img.height;
  this->output.width = this->img.width;

  this->output->data = (Pixel*)malloc(3 * this->output.height * this->output.width * sizeof(Pixel));


  for (int i = 0; i < this->output.height; i++) {
    for (int j = 0; j < this->output.width; j++) {
      //assign red
      if(this->img->data[i * this->img.width + j].R > this->img2->data[i * this->img2.width + j].R)
        this->output->data[i * this->output.width + j].R = 
              this->img->data[i * this->img.width + j].R - this->img2->data[i * this->img2.width + j].R;
      else
        this->output->data[i * this->output.width + j].R = 0;

      //assign green
      if(this->img->data[i * this->img.width + j].G > this->img2->data[i * this->img2.width + j].G)
        this->output[i * output->width + j].G = 
              this->img->data[i * this->img.width + j].G - this->img2->data[i * this->img2.width + j].G;
      else
        this->output->data[i * this->output.width + j].G = 0;

      //assign blue
      if(this->img->data[i * this->img.width + j].B > this->img2->data[i * this->img2.width + j].B)
        this->output->data[i * this->output.width + j].B =
              this->img->data[i * this->img.width + j].B - this->img2->data[i * this->img2.width + j].B;
      else
        this->output->data[i * this->output.width + j].B = 0;
    }
  }
}

void Grayscale::Execute() {
  this->output.height = this->img.height;
  this->output.width = this->img.width;

  this->output->data = (Pixel*)malloc(3 * this->output.height * this->output.width * sizeof(Pixel));


  for (int i = 0; i < this->output.height; i++) {
    for (int j = 0; j < this->output.width; j++) {
      this->output->data[i * this->output.width + j].R = this->img->data[i * this->img.width + j].R/5;
      this->output->data[i * this->output.width + j].G = this->img->data[i * this->img.width + j].G/2;
      this->output->data[i * this->output.width + j].B = this->img->data[i * this->img.width + j].B/4;
    }
  }
}

void Blur::Execute() {
  this->output.height = this->img.height;
  this->output.width = this->img.width;

  this->output->data = (Pixel*)malloc(3 * this->output.height * this->output.width * sizeof(Pixel));


  for (int i = 0; i < this->output.height; i++) {
    for (int j = 0; j < this->output.width; j++) {
      if ((i == 0 || i == this->output.height) && (j == 0 || j == this->output.width)) {
        this->output->data[i * this->output.width + j].R = this->img->data[i * this->img->width + j].R;
        this->output->data[i * this->output.width + j].G = this->img->data[i * this->img->width + j].G;
        this->output->data[i * this->output.width + j].B = this->img->data[i * this->img->width + j].B;
      } else {
        this->output->data[i * this->output.width + j].R = 
                      this->img->data[(i+1) * this->img.width + j].R/8 +
                      this->img->data[(i-1) * this->img.width + j].R/8 + 
                      this->img->data[i * this->img.width + (j+1)].R/8 + 
                      this->img->data[i * this->img.width + (j-1)].R/8 +
                      this->img->data[(i+1) * this->img.width + (j+1)].R/8 +
                      this->img->data[(i-1) * this->img.width + (j-1)].R/8 +
                      this->img->data[(i+1) * this->img.width + (j-1)].R/8 +
                      this->img->data[(i-1) * this->img.width + (j+1)].R/8;
      
        this->output->data[i * this->output.width + j].G = 
                      this->img->data[(i+1) * this->img.width + j].G/8 +
                      this->img->data[(i-1) * this->img.width + j].G/8 + 
                      this->img->data[i * this->img.width + (j+1)].G/8 + 
                      this->img->data[i * this->img.width + (j-1)].G/8 +
                      this->img->data[(i+1) * this->img.width + (j+1)].G/8 +
                      this->img->data[(i-1) * this->img.width + (j-1)].G/8 +
                      this->img->data[(i+1) * this->img.width + (j-1)].G/8 +
                      this->img->data[(i-1) * this->img.width + (j+1)].G/8;

        this->output->data[i * this->output.width + j].B = 
                      this->img->data[(i+1) * this->img.width + j].B/8 +
                      this->img->data[(i-1) * this->img.width + j].B/8 + 
                      this->img->data[i * this->img.width + (j+1)].B/8 + 
                      this->img->data[i * this->img.width + (j-1)].B/8 +
                      this->img->data[(i+1) * this->img.width + (j+1)].B/8 +
                      this->img->data[(i-1) * this->img.width + (j-1)].B/8 +
                      this->img->data[(i+1) * this->img.width + (j-1)].B/8 +
                      this->img->data[(i-1) * this->img.width + (j+1)].B/8;
      }
    }
  } 
}

/*end of file*/
