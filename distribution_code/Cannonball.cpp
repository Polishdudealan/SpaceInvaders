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
