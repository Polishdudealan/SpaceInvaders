#include "Powerups.h"

using namespace Constants;

Powerups::Powerups(int width = 3, int height = 3): type(LIFE), active(false), Sprite(-5, -5, width, height) {}

void Powerups::draw(Signal& matrix) {
  if (active){
    uint16_t color = Constants::p_color(type).to_333();
    matrix.drawPixel(x, y + 1, color);
    matrix.drawPixel(x + 1, y, color);
    matrix.drawPixel(x + 1, y + 1, color);
    matrix.drawPixel(x + 1, y + 2, color);
    matrix.drawPixel(x + 2, y + 1, color);
  } else {
    erase(matrix);
  }
}

void Powerups :: move() {
  if (active) {
    if (y<=31){
      y++;  
    } else{
      active = false;
    }
  }
}

bool Powerups :: check_active() const {
  return active;
}

void Powerups :: deactivate() {
  x = -5;
  y = -5; 
  active = false;
}

PowerupType Powerups::getType() const {
  return type;
}

void Powerups::spawn(int arg_x, int arg_y, PowerupType arg_type){
  x = arg_x;
  y = arg_y;
  type = arg_type;
  active = true;
}
