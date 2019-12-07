#include "Signal.h"

Signal::Signal(): RGBmatrixPanel(0, 0, 0, 0, 0, 0, false) {
  Serial1.begin(38400);
  //Serial2.begin(19200);
  }
 
void Signal::drawPixel(int16_t x, int16_t y, uint16_t c) {
  char c1 = (c & 0xFF00) >> 8;
  char c2 = c & 0x00FF;
  char data1[8] = {DRAWPIXEL, x, y, 0, 0, c1, c2, 0};
  char data2[8] = {DRAWPIXEL, x, y - 16, 0, 0, c1, c2, 0};
  Serial1.write(data1, 8);
  //Serial2.write(data2, 8);
  
}

void Signal::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c){
  char c1 = (c & 0xFF00) >> 8;
  char c2 = c & 0x00FF;
  char data1[8] = {DRAWRECT, x, y, w, h, c1, c2, 0};
  char data2[8] = {DRAWRECT, x, y - 16, w, h, c1, c2, 0};
  Serial1.write(data1, 8);

  //Serial2.write(data2, 8);
}

void Signal::fillScreen(uint16_t c){
  char c1 = (c & 0xFF00) >> 8;
  char c2 = c & 0x00FF;
  char data1[8] = {FILLSCREEN, 0, 0, 0, 0, c1, c2, 0};
  Serial1.write(data1, 8);
  //Serial.println(Serial1.availableForWrite());
  //Serial2.write(data1, 8);
}

void Signal::setCursor(int16_t x, int16_t y){
  char data1[8] = {SETCURSOR, x, y, 0, 0, 0, 0, 0};
  char data2[8] = {SETCURSOR, x, y, 0, 0, 0, 0, 0};
  Serial1.write(data1, 8);
  //Serial2.write(data2, 8);
}

void Signal::print(char character){
  char data1[8] = {PRINTCHAR, 0, 0, 0, 0, 0, 0, character};
  char data2[8] = {PRINTCHAR, 0, 0, 0, 0, 0, 0, character};
  Serial1.write(data1, 8);
  //Serial2.write(data2, 8);
}

void Signal::setTextColor(int16_t c){
  char c1 = (c & 0xFF00) >> 8;
  char c2 = c & 0x00FF;
  char data1[8] = {SETTEXTCOLOR, 0, 0, 0, 0, c1, c2, 0};
  Serial1.write(data1, 8);
  //Serial2.write(data1, 8);
}
