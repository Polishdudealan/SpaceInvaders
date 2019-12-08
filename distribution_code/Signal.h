#pragma once

#ifndef LIBRARIES
  #define LIBRARIES
  #include <gamma.h>
  #include <RGBmatrixPanel.h>
  #include <Adafruit_GFX.h>
#endif

class Signal{
  public:
    Signal();
    enum Datatype {DRAWPIXEL, FILLRECT, FILLSCREEN, SETCURSOR, PRINTCHAR, SETTEXTCOLOR};
    void drawPixel(int16_t x, int16_t y, uint16_t c);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillScreen(uint16_t color);
    void setCursor(int16_t x, int16_t y);
    void print(char character);
    void setTextColor(int16_t color);
    uint16_t Signal::Color333(uint8_t r, uint8_t g, uint8_t b);
};
