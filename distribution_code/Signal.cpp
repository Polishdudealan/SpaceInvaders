#include "Signal.h"

Signal::Signal(): RGBmatrixPanel(0, 0, 0, 0, 0, 0, false) {}
 
void Signal::drawPixel(int16_t x, int16_t y, uint16_t c) {
  char data1[7] = {DRAWPIXEL, x, y, 0, 0, c, 0};
  char data2[7] = {DRAWPIXEL, x, y - 16, 0, 0, c, 0};
  Serial1.write(data1, 112);
  Serial2.write(data2, 112);
}

void Signal::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  char data1[7] = {DRAWRECT, x, y, w, h, color, 0};
  char data2[7] = {DRAWRECT, x, y - 16, w, h, color, 0};
  Serial1.write(data1, 112);
  Serial2.write(data2, 112);
}

void Signal::fillScreen(uint16_t color){
  char data1[7] = {FILLSCREEN, 0, 0, 0, 0, color, 0};
  Serial1.write(data1, 112);
  Serial2.write(data1, 112);
}

void Signal::setCursor(int16_t x, int16_t y){
  char data1[7] = {SETCURSOR, x, y, 0, 0, 0, 0};
  char data2[7] = {SETCURSOR, x, y, 0, 0, 0, 0};
  Serial1.write(data1, 112);
  Serial2.write(data2, 112);
}

void Signal::print(int16_t character){
  char data1[7] = {PRINTCHAR, 0, 0, 0, 0, 0, character};
  char data2[7] = {PRINTCHAR, 0, 0, 0, 0, 0, character};
  Serial1.write(data1, 112);
  Serial2.write(data2, 112);
}

void Signal::setTextColor(int16_t color){
  char data1[7] = {SETTEXTCOLOR, 0, 0, 0, 0, color, 0};
  Serial1.write(data1, 112);
  Serial2.write(data1, 112);
}
