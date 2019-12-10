#include "Signal.h"

Signal::Signal() {
  Serial1.begin(115200);
  Serial2.begin(115200);
}
  
//stole from RGGmatrixPanel code
uint16_t Signal::Color333(uint8_t r, uint8_t g, uint8_t b) {
  // RRRrrGGGgggBBBbb
  return ((r & 0x7) << 13) | ((r & 0x6) << 10) |
         ((g & 0x7) <<  8) | ((g & 0x7) <<  5) |
         ((b & 0x7) <<  2) | ((b & 0x6) >>  1);
}
 
 
void Signal::drawPixel(int16_t x, int16_t y, uint16_t c) {
  char c1 = (c & 0xFF00) >> 8;
  char c2 = c & 0x00FF;
  char data1[8] = {DRAWPIXEL, x, y, 1, 1, c1, c2, 1};
  char data2[8] = {DRAWPIXEL, x, y - 16, 1, 1, c1, c2, 1};
  Serial1.write(data1, 8);
  Serial2.write(data2, 8);  
}

void Signal::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c){
  char c1 = (c & 0xFF00) >> 8;
  char c2 = c & 0x00FF;
  char data1[8] = {FILLRECT, x, y, w, h, c1, c2, 1};
  char data2[8] = {FILLRECT, x, y - 16, w, h, c1, c2, 1};
  Serial1.write(data1, 8);
  Serial2.write(data2, 8);
}

void Signal::fillScreen(uint16_t c){
  char c1 = (c & 0xFF00) >> 8;
  char c2 = c & 0x00FF;
  char data1[8] = {FILLSCREEN, 1, 1, 1, 1, c1, c2, 1};
  Serial1.write(data1, 8);
  Serial2.write(data1, 8);
}

void Signal::setCursor(int16_t x, int16_t y){
  char data1[8] = {SETCURSOR, x, y, 1, 1, 1, 1, 1};
  char data2[8] = {SETCURSOR, x, y - 16, 1, 1, 1, 1, 1};
  Serial1.write(data1, 8);
  Serial2.write(data2, 8);
}

void Signal::print(char character){
  char data1[8] = {PRINTCHAR, 1, 1, 1, 1, 1, 1, character};
  Serial1.write(data1, 8);
  Serial2.write(data1, 8);
}

void Signal::setTextColor(int16_t c){
  char c1 = (c & 0xFF00) >> 8;
  char c2 = c & 0x00FF;
  char data1[8] = {SETTEXTCOLOR, 1, 1, 1, 1, c1, c2, 1};
  Serial1.write(data1, 8);
  Serial2.write(data1, 8);
}
