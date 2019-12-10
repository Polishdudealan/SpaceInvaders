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

void Cannonball::drawNuke(int frame, Signal& matrix) {
    switch (frame) {
        case 1:
//top line
        matrix.fillRect(12,19,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,20,3,1, ORANGE.to_333());
        matrix.fillRect(19,20,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,21,3,1, ORANGE.to_333());
        matrix.fillRect(21,21,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,22,2,1, ORANGE.to_333());
        matrix.fillRect(22,22,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,23,2,1, ORANGE.to_333());
        matrix.fillRect(23,23,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,23,1,5, ORANGE.to_333());
        matrix.fillRect(23,23,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(6,28,2,1, ORANGE.to_333());
        matrix.fillRect(23,28,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,28,15,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(11,28,1,3, ORANGE.to_333());     
        matrix.fillRect(19,28,1,3, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(11,31,9,1, ORANGE.to_333());     
        break;

        case 2:

        break;

        case 3:

        break;

        case 4:

        break;

        case 5:

        break;
        
        
      }
  }
