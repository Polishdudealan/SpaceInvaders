#include "Cannonball.h"

using namespace Constants;

Cannonball::Cannonball(BallType type = PLAYER, int width = 1, int height = 2): fired(false), type(type), Sprite(-10, -10, width, height) {}

void Cannonball::reset() {
  x = -10;
  y = -10;
  fired = false;
}
    
bool Cannonball::hasBeenFired() const {
  return fired;
}

void Cannonball::fire(int x_arg, int y_arg) {
  x = x_arg;
  y = y_arg;
  fired = true;
}

void Cannonball::move() {
  if (y >= 7) {
    y--;
  }
   else {
    fired = false;
  }
}

void Cannonball::hit() {
  x = -10;
  y = -10;
  fired = false;
}

void Cannonball::draw(Signal& matrix) {
  if(fired){
    matrix.drawPixel(x, y, RED.to_333());
    matrix.drawPixel(x, y + 1, RED.to_333()); 
  }
  else {
    erase(matrix);
  }
}
