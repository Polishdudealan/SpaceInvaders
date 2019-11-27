#include "Color.h"

Color::Color(){
	red = 0;
	green = 0;
	blue = 0;
}
 
Color::Color(int r, int g, int b): red(r), green(g), blue(b) {}

// taken directly from RGBMatrixPanel for organization purposes
// sorry for redundency but this prevents having to pass around
// an entire matrix object for every color
// Promote 3/3/3 RGB to Adafruit_GFX 5/6/5
uint16_t Color::to_333() const {
  // RRRrrGGGgggBBBbb
  return ((red & 0x7) << 13) | ((red & 0x6) << 10) |
         ((green & 0x7) <<  8) | ((green & 0x7) <<  5) |
         ((blue & 0x7) <<  2) | ((blue & 0x6) >>  1);
}
