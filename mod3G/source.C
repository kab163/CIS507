#include <source.h>
#include <logging.h>
#include <iostream>

Source::Source() {
  img.SetSource(this);
}

Image* Source::GetOutput()
{
  return &img;
}

void Source::Update() {
  char msg[50];
  sprintf(msg, "Executing...");
  Logger::LogEvent(msg);
  
  Execute();

  sprintf(msg, "Done!");
  Logger::LogEvent(msg);
}

Color::Color(int _w, int _h, unsigned char _r, unsigned char _g, unsigned char _b) {
  width = _w;
  height = _h;

  R = _r;
  G = _g;
  B = _b;
}

/*end of file*/
