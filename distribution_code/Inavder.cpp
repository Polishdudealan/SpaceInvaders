#include "Invader.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

Color invaderColors[] = {WHITE, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};

Invader::Invader(int x_arg = 0, int y_arg = 0, int strength_arg = 0, int height = 4, int width = 4): x(x_arg), y(y_arg), strength(strength_arg), height(height), width(width) {}

int Invader::getStrength() const {
  return strength;
}

void Invader::move() {
  y++;
}

// draws the Invader if its strength is greater than 0
// calls: draw_with_rgb
void Invader::draw(RGBmatrixPanel& matrix) {
  if (strength != 0) {
    draw_with_rgb(invaderColors[strength % 7], invaderColors[(strength / 7 + 5) % 7], matrix);      
  }
}

// draws black where the Invader used to be
// calls: draw_with_rgb
void Invader::erase(RGBmatrixPanel& matrix) {
  draw_with_rgb(BLACK, BLACK, matrix);
}

// Invader is hit by a Cannonball.
// Modifies: strength
void Invader::hit() {
  strength--;
}

void Invader::draw_with_rgb(Color body_color, Color eye_color, RGBmatrixPanel& matrix) {
  uint16_t b_col = body_color.to_333();
  uint16_t e_col = eye_color.to_333();
  uint16_t blk = BLACK.to_333();
  matrix.fillRect(x, y, 4, 4, b_col);
  matrix.drawPixel(x, y, blk);
  matrix.drawPixel(x+3, y, blk);
  matrix.drawPixel(x+1, y+3, blk);
  matrix.drawPixel(x+2, y+3, blk);
  matrix.drawPixel(x+1,y+1,e_col);
  matrix.drawPixel(x+2,y+1,e_col);
}
