#include "Invader.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

Invader::Invader(int x_arg = 0, int y_arg = 0, int strength_arg = 0, bool dropsPUp = false, int height = 4, int width = 4): strength(strength_arg), dropsPUp(dropsPUp), Sprite(x_arg, y_arg, width, height) {}

// sets values for private data members
void Invader::initialize(int x_arg, int y_arg, int strength_arg) {
  x = x_arg;
  y = y_arg;
  strength = strength_arg;
}

int Invader::getStrength() const {
  return strength;
}

void Invader::move() {
  y++;
}

void Invader::draw(Signal& matrix) {
  if (strength != 0) {
    draw_with_rgb(num_to_color(strength % 7), num_to_color((strength / 7 + 5) % 7), matrix);      
  } else {
    erase(matrix);
  }
}

void Invader::hit() {
  strength--;
}

void Invader::draw_with_rgb(Color body_color, Color eye_color, Signal& matrix) {
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

bool Invader::drops(){
  return dropsPUp;
}

Color Invader::num_to_color(int x){
  switch (x) {
    case 0:
      return WHITE;
      break;
    case 1:
      return RED;
      break;
    case 2:
      return ORANGE;
      break;
    case 3:
      return YELLOW;
      break;
    case 4:
      return GREEN;
      break;
    case 5:
      return BLUE;
      break;
    case 6:
      return PURPLE;
      break;
    default:
      return BLACK;
  }
}
