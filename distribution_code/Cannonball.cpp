#include "Cannonball.h"
#include "Constants.h"
using namespace Constants;

Cannonball::Cannonball(int width = 1, int height = 2): fired(false), Sprite(-10, -10, width, height) {}

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
  if (y >= 0) {
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

void Cannonball::draw(RGBmatrixPanel& matrix) {
  if(fired){
    matrix.drawPixel(x, y, RED.to_333());
    matrix.drawPixel(x, y - 1, RED.to_333()); 
  }
  else {
    erase(matrix);
  }
}