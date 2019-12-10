#include "Cannonball.h"

using namespace Constants;

Cannonball::Cannonball(BallType type = STANDARD, int width = 1, int height = 2): fired(false), type(type), Sprite(-10, -10, width, height) {}

void Cannonball::reset() {
  x = -10;
  y = -10;
  fired = false;
}
    
bool Cannonball::hasBeenFired() const {
  return fired;
}

BallType Cannonball::getType(){
  return type;
}

void Cannonball::setType(BallType arg_type) {
  type = arg_type;
}

void Cannonball::fire(int x_arg, int y_arg) {
  x = x_arg;
  y = y_arg;
  fired = true;
}

void Cannonball::tick() {
  if (type == INVADER){
    if (y <= 31){
      y++;
    } else {
      fired = false;
    }
  } else {
    if (y >= 7) {
      y--;
    } else {
      fired = false;
    }      
  }
}

void Cannonball::hit() {
  x = -10;
  y = -10;
  fired = false;
}

void Cannonball::draw(Signal& matrix) {
  if(fired){
    uint16_t b_col = b_color(type).to_333();
    matrix.drawPixel(x, y, b_col);
    matrix.drawPixel(x, y + 1, b_col); 
  }
  else {
    erase(matrix);
  }
}
