#include "Powerups.h"


Powerups::Powerups(): Sprite(-10, -10, 3, 3) {}

void Powerups::draw(RGBmatrixPanel& matrix) {
  draw__pup_with_rgb(RED, matrix);
}

void Powerups::draw__pup_with_rgb(Color color, RGBmatrixPanel& matrix) {
  matrix.drawPixel(x, y + 1, color.to_333());
  matrix.drawPixel(x + 1, y, color.to_333());
  matrix.drawPixel(x + 1, y + 1, color.to_333());
  matrix.drawPixel(x + 1, y + 2, color.to_333());
  matrix.drawPixel(x + 2, y + 1, color.to_333());
}

Color Powerups::p_color(PowerupType power){
  switch (power) {
    case LIFE:
      return RED;
      break;
    default:
      return BLACK;
  }
}
