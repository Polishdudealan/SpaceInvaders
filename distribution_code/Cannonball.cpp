#include "Cannonball.h"

using namespace Constants;

Cannonball::Cannonball(BallType type = STANDARD, int width = 1, int height = 2): fired(false), exploding(false), explodingDuration(0), type(type), Sprite(-10, -10, width, height) {}

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
  width = 1;
  height = 2;
  exploding = false;
  fired = true;
}

void Cannonball::tick() {
  if (!fired) return;
  
  if (type == INVADER){
    if (y <= 31){
      y++;
    } else {
      fired = false;
    }
  } else {
    if (exploding) {
      if (explodingDuration < 5) {
        explodingDuration++;
        width+=2;
        height+=2;
        x--;
        y--;
        upd();
      } else {
        explodingDuration = 0;
        fired = false;
        upd();
      }
    } else if (y >= 7) {
      y--;
    } else {
      fired = false;
    }      
  }
}

void Cannonball::hit() {
  if (type == BOMB){
    if (!exploding){
      exploding = true;
      height = 1;
      explodingDuration = 0; 
    }
  } else {
    x = -10;
    y = -10;
    fired = false;
  }
}

void Cannonball::draw(Signal& matrix) {
  if(fired){
    uint16_t b_col = b_color(type).to_333();
    matrix.fillRect(x, y, width, height, b_col);
  }
  else {
    erase(matrix);
  }
}
