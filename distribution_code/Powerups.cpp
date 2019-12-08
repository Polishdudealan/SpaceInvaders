#include "Powerups.h"


Powerups::Powerups(): Sprite(-10, -10, 3, 3) {}

void Powerups::draw(Signal& matrix) {
  draw__pup_with_rgb(RED, matrix);
}

void Powerups::draw__pup_with_rgb(Color color, Signal& matrix) {
  matrix.drawPixel(x, y + 1, color.to_333());
  matrix.drawPixel(x + 1, y, color.to_333());
  matrix.drawPixel(x + 1, y + 1, color.to_333());
  matrix.drawPixel(x + 1, y + 2, color.to_333());
  matrix.drawPixel(x + 2, y + 1, color.to_333());
}

Color Powerups::p_color(PowerupType power) {
  switch (power) {
    case LIFE:
      return RED;
      break;
    default:
      return BLACK;
  }
}

void Powerups :: move() {
    if (active) {
       y++;  
    }
}

bool Powerups :: check_active() {
  return active;
  }

void Powerups :: deactivate() {
    active = false;
  }
