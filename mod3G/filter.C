#include <image.h>
#include <filter.h>
#include <assert.h>
#include <stdlib.h>
#include <logging.h>

using namespace std;

//void Filter::SetInput(Image _img) {this->img = _img; }

//void Filter::SetInput2(Image _img2) {this->img2 = _img2; }

//Image Filter::GetOutput() {return this->output; }

void Blender::SetFactor(double _factor) {this->factor = _factor; }

void Filter::Update() {
  char msg[50];

  output = &img;
  if(img1 != NULL) {
    sprintf(msg, "Updating...");
    Logger::LogEvent(msg);
    img1->Update();
  }

  if(img2 != NULL) {
    sprintf(msg, "Updating...");
    Logger::LogEvent(msg);
    img2->Update();
  }

  sprintf(msg, "Executing...");
  Logger::LogEvent(msg);
  Execute();
}

void Shrinker::Execute()
{
  if(img1 == NULL){
    char msg[50];
    sprintf(msg, "input NULL");
    DataFlowException e(msg);
    throw e;
  }
 
  this->output->width = (this->img1->width + 1) / 2;
  this->output->height = (this->img1->height + 1) / 2;

  this->output->data = (Pixel*)malloc(3 * this->output->width * this->output->height * sizeof(Pixel));

  for(int i = 0; i < this->output->height; i++) {
    for (int j = 0; j < this->output->width; j++) {
      this->output->data[i * this->output->width + j] = this->img1->data[(2*i) * this->img1->width + (2*j)];
    }
  }
}

void LRCombine::Execute() {
  //assert(this->img->width == this->img2->width);
  
  this->output->width = 2 * this->img1->width;
  this->output->height = this->img1->height;

  this->output->data = (Pixel*)malloc(3 * this->output->width * this->output->height * sizeof(Pixel));

  for(int i = 0; i < this->output->height; i++) {
    for(int j = 0; j < this->output->width; j++) {
      if (j >= 0 && j < this->img1->width) this->output->data[i * this->output->width + j] = this->img1->data[i * this->img1->width + j];
      else this->output->data[i * this->output->width + j] = this->img2->data[i * this->img2->width + (j - this->img2->width)];
    }
  }
}

void TBCombine::Execute() {
  //assert(this->img->height == this->img2->height);

  this->output->width = this->img2->width;
  this->output->height = 2* this->img2->height;

  this->output->data = (Pixel*)malloc(3 * this->output->width * this->output->height * sizeof(Pixel));

  for(int i = 0; i < this->output->height; i++) {
    for(int j = 0; j < this->output->width; j++) {
      if (i >= 0 && i < this->img2->height) this->output->data[i * this->output->width + j] = this->img2->data[i * this->img2->width + j];
      else this->output->data[i * this->output->width + j] = this->img1->data[(i-this->img1->height) * this->img1->width + j];
    }
  }

}

void Blender::Execute() {
  //assert(this->img.height == this->img2.height);
  //assert(this->img.width == this->img2.width);

  this->output->height = this->img1->height;
  this->output->width = this->img1->width;

  this->output->data = (Pixel*)malloc(3 * this->output->height * this->output->width * sizeof(Pixel));

  for (int i = 0; i < this->output->height; i++) {
    for (int j = 0; j < this->output->width; j++) {
      this->output->data[i * this->output->width + j].R = (this->factor * 
                                               (this->img1->data[i * this->output->width + j].R)) + 
                                               ((1-this->factor) * (this->img2->data[i * this->output->width + j].R));
      this->output->data[i * this->output->width + j].G = (this->factor * 
                                               (this->img1->data[i * this->output->width + j].G)) + 
                                               ((1-this->factor) * (this->img2->data[i * this->output->width + j].G));
      this->output->data[i * this->output->width + j].B = (this->factor * 
                                               (this->img1->data[i * this->output->width + j].B)) + 
                                               ((1-this->factor) * (this->img2->data[i * this->output->width + j].B));
    }
  }

}

void Mirror::Execute() {
  this->output->height = this->img1->height;
  this->output->width = this->img1->width;

  this->output->data = (Pixel*)malloc(3 * this->output->height * this->output->width * sizeof(Pixel));


  for (int i = 0; i < this->output->height; i++) {
    for (int j = 0; j < this->output->width; j++) {
      this->output->data[i * this->output->width + j] = this->img1->data[(this->img1->height-1 - i) * 
                                                        this->img1->width + j];
    }
  }
}

void Rotate::Execute() {
  this->output->height = this->img1->height;
  this->output->width = this->img1->width;

  this->output->data = (Pixel*)malloc(3 * this->output->height * this->output->width * sizeof(Pixel));


  for (int i = 0; i < this->output->height; i++) {
    for (int j = 0; j < this->output->width; j++) {
      this->output->data[i * this->output->width + j] = this->img1->data[(this->img1->height-1 - i) * 
                                                        this->img1->width + j];
    }
  }
}

void Subtract::Execute() {
  this->output->height = this->img1->height;
  this->output->width = this->img1->width;

  this->output->data = (Pixel*)malloc(3 * this->output->height * this->output->width * sizeof(Pixel));


  for (int i = 0; i < this->output->height; i++) {
    for (int j = 0; j < this->output->width; j++) {
      //assign red
      if(this->img1->data[i * this->img1->width + j].R > this->img2->data[i * this->img2->width + j].R)
        this->output->data[i * this->output->width + j].R =
              this->img1->data[i * this->img1->width + j].R - this->img2->data[i * this->img2->width + j].R;
      else
        this->output->data[i * this->output->width + j].R = 0;

      //assign green
      if(this->img1->data[i * this->img1->width + j].G > this->img2->data[i * this->img2->width + j].G)
        this->output->data[i * this->output->width + j].G =
              this->img1->data[i * this->img1->width + j].G - this->img2->data[i * this->img2->width + j].G;
      else
        this->output->data[i * this->output->width + j].G = 0;

      //assign blue
      if(this->img1->data[i * this->img1->width + j].B > this->img2->data[i * this->img2->width + j].B)
        this->output->data[i * this->output->width + j].B =
                    this->img1->data[i * this->img1->width + j].B - this->img2->data[i * this->img2->width + j].B;
      else
        this->output->data[i * this->output->width + j].B = 0;
    }
  }
}

void Grayscale::Execute() {
  this->output->height = this->img1->height;
  this->output->width = this->img1->width;

  this->output->data = (Pixel*)malloc(3 * this->output->height * this->output->width * sizeof(Pixel));


  for (int i = 0; i < this->output->height; i++) {
    for (int j = 0; j < this->output->width; j++) {
      this->output->data[i * this->output->width + j].R = this->img1->data[i * this->img1->width + j].R/5;
      this->output->data[i * this->output->width + j].G = this->img1->data[i * this->img1->width + j].G/2;
      this->output->data[i * this->output->width + j].B = this->img1->data[i * this->img1->width + j].B/4;
    }
  }
}

void Blur::Execute() {
  this->output->height = this->img1->height;
  this->output->width = this->img1->width;

  this->output->data = (Pixel*)malloc(3 * this->output->height * this->output->width * sizeof(Pixel));


  for (int i = 0; i < this->output->height; i++) {
    for (int j = 0; j < this->output->width; j++) {
      if ((i == 0 || i == (this->output->height - 1)) && (j == 0 || j == (this->output->width-1))) {
        this->output->data[i * this->output->width + j] = this->img1->data[i * this->img1->width + j];
      } else {
        this->output->data[i * this->output->width + j].R = this->img1->data[(i+1) * this->img1->width + j].R/8 +
                                                           this->img1->data[(i+1) * this->img1->width + (j+1)].R/8 +
                                                           this->img1->data[(i-1) * this->img1->width + j].R/8 +
                                                           this->img1->data[(i-1) * this->img1->width + (j-1)].R/8 +
                                                           this->img1->data[i * this->img1->width + (j+1)].R/8 +
                                                           this->img1->data[(i+1) * this->img1->width + (j+1)].R/8 +
                                                           this->img1->data[i * this->img1->width + (j-1)].R/8 +
                                                           this->img1->data[(i-1) * this->img1->width + (j-1)].R/8;

        this->output->data[i * this->output->width + j].G = this->img1->data[(i+1) * this->img1->width + j].G/8 +
                                                           this->img1->data[(i+1) * this->img1->width + (j+1)].G/8 +
                                                           this->img1->data[(i-1) * this->img1->width + j].G/8 +
                                                           this->img1->data[(i-1) * this->img1->width + (j-1)].G/8 +
                                                           this->img1->data[i * this->img1->width + (j+1)].G/8 +
                                                           this->img1->data[(i+1) * this->img1->width + (j+1)].G/8 +
                                                           this->img1->data[i * this->img1->width + (j-1)].G/8 +
                                                           this->img1->data[(i-1) * this->img1->width + (j-1)].G/8;
      
        this->output->data[i * this->output->width + j].B = this->img1->data[(i+1) * this->img1->width + j].B/8 +
                                                           this->img1->data[(i+1) * this->img1->width + (j+1)].B/8 +
                                                           this->img1->data[(i-1) * this->img1->width + j].B/8 +
                                                           this->img1->data[(i-1) * this->img1->width + (j-1)].B/8 +
                                                           this->img1->data[i * this->img1->width + (j+1)].B/8 +
                                                           this->img1->data[(i+1) * this->img1->width + (j+1)].B/8 +
                                                           this->img1->data[i * this->img1->width + (j-1)].B/8 +
                                                           this->img1->data[(i-1) * this->img1->width + (j-1)].B/8;
      }
    }
  }
}



void Color::Execute() {
  if ( R < 0 || R > 255) {
        char msg[50];
        sprintf(msg, "invalid red color value");
        DataFlowException e(msg);
        throw e;
    }

    if ( G < 0 || G > 255) {
        char msg[50];
        sprintf(msg, "invalid green color value");
        DataFlowException e(msg);
        throw e;
    }

    if ( B < 0 || B > 255) {
        char msg[50];
        sprintf(msg, "invalid blue color value");
        DataFlowException e(msg);
        throw e;
    }

    Pixel *data = NULL;
    int index = 0;

    data = (Pixel *) malloc(width * height * sizeof(Pixel));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            index = i * width + j;
            data[index].R = R;
            data[index].G = G;
            data[index].B = B;
        }
    }

    img.ResetSize(width, height);
    img.SetData(data);
}

void CheckSum::OutputCheckSum(const char* filename) {
  if(img1 == NULL) {
    char msg[50];
    sprintf(msg, "Invalid Input");
    DataFlowException e(msg);
    throw e;
  }

  FILE *fp = fopen(filename, "w");
  int width = 0, height = 0, index = 0;

  width = img1->GetWidth();
  height = img1->GetHeight();

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      index = i * width + j;
            red += img1->GetData()[index].R;
            green += img1->GetData()[index].G;
            blue += img1->GetData()[index].B;
        }
    }

    fprintf(fp, "CHECKSUM: %u, %u, %u\n", red, green, blue);
    fclose(fp);
}


/*end of file*/
