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
        x--;
        if (y >=7) {
          height+=2;
          y--;
        }
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
        matrix.fillRect(23,22,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,23,2,1, ORANGE.to_333());
        matrix.fillRect(24,23,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,23,1,5, ORANGE.to_333());
        matrix.fillRect(25,23,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,28,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,28,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,28,1,3, ORANGE.to_333());     
        matrix.fillRect(19,28,1,3, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333());     
        break;

        case 2:
//top line
        matrix.fillRect(12,18,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,19,3,1, ORANGE.to_333());
        matrix.fillRect(19,19,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,20,3,1, ORANGE.to_333());
        matrix.fillRect(21,20,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,21,2,1, ORANGE.to_333());
        matrix.fillRect(23,21,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,22,2,1, ORANGE.to_333());
        matrix.fillRect(24,22,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,22,1,5, ORANGE.to_333());
        matrix.fillRect(25,22,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,27,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,27,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,27,1,4, ORANGE.to_333());     
        matrix.fillRect(19,27,1,4, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 
        break;

        case 3:
//top line
        matrix.fillRect(12,17,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,18,3,1, ORANGE.to_333());
        matrix.fillRect(19,18,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,19,3,1, ORANGE.to_333());
        matrix.fillRect(21,19,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,20,2,1, ORANGE.to_333());
        matrix.fillRect(23,20,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,21,2,1, ORANGE.to_333());
        matrix.fillRect(24,21,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,21,1,5, ORANGE.to_333());
        matrix.fillRect(25,21,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,26,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,26,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,26,1,5, ORANGE.to_333());     
        matrix.fillRect(19,26,1,5, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 
        break;

        case 4:
//top line
        matrix.fillRect(12,16,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,17,3,1, ORANGE.to_333());
        matrix.fillRect(19,17,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,18,3,1, ORANGE.to_333());
        matrix.fillRect(21,18,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,19,2,1, ORANGE.to_333());
        matrix.fillRect(23,19,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,20,2,1, ORANGE.to_333());
        matrix.fillRect(24,20,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,20,1,5, ORANGE.to_333());
        matrix.fillRect(25,20,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,25,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,25,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,25,1,6, ORANGE.to_333());     
        matrix.fillRect(19,25,1,6, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 
        break;

        case 5:
//top line
        matrix.fillRect(12,15,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,16,3,1, ORANGE.to_333());
        matrix.fillRect(19,16,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,17,3,1, ORANGE.to_333());
        matrix.fillRect(21,17,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,18,2,1, ORANGE.to_333());
        matrix.fillRect(23,18,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,19,2,1, ORANGE.to_333());
        matrix.fillRect(24,19,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,19,1,5, ORANGE.to_333());
        matrix.fillRect(25,19,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,24,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,24,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,24,1,7, ORANGE.to_333());     
        matrix.fillRect(19,24,1,7, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 
        break;

        case 6:
//top line
        matrix.fillRect(12,14,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,15,3,1, ORANGE.to_333());
        matrix.fillRect(19,15,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,16,3,1, ORANGE.to_333());
        matrix.fillRect(21,16,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,17,2,1, ORANGE.to_333());
        matrix.fillRect(23,17,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,18,2,1, ORANGE.to_333());
        matrix.fillRect(24,18,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,18,1,5, ORANGE.to_333());
        matrix.fillRect(25,18,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,23,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,23,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,23,1,8, ORANGE.to_333());     
        matrix.fillRect(19,23,1,8, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 
        break;

      case 7:
//top line
        matrix.fillRect(12,13,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,14,3,1, ORANGE.to_333());
        matrix.fillRect(19,14,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,15,3,1, ORANGE.to_333());
        matrix.fillRect(21,15,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,16,2,1, ORANGE.to_333());
        matrix.fillRect(23,16,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,17,2,1, ORANGE.to_333());
        matrix.fillRect(24,17,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,17,1,5, ORANGE.to_333());
        matrix.fillRect(25,17,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,22,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,22,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,22,1,9, ORANGE.to_333());     
        matrix.fillRect(19,22,1,9, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 
        break;

      case 8:
//top line
        matrix.fillRect(12,12,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,13,3,1, ORANGE.to_333());
        matrix.fillRect(19,13,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,14,3,1, ORANGE.to_333());
        matrix.fillRect(21,14,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,15,2,1, ORANGE.to_333());
        matrix.fillRect(23,15,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,16,2,1, ORANGE.to_333());
        matrix.fillRect(24,16,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,16,1,5, ORANGE.to_333());
        matrix.fillRect(25,16,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,21,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,21,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,21,1,10, ORANGE.to_333());     
        matrix.fillRect(19,21,1,10, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 
        break;

case 9:
//top line
        matrix.fillRect(12,11,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,12,3,1, ORANGE.to_333());
        matrix.fillRect(19,12,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,13,3,1, ORANGE.to_333());
        matrix.fillRect(21,13,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,14,2,1, ORANGE.to_333());
        matrix.fillRect(23,14,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,15,2,1, ORANGE.to_333());
        matrix.fillRect(24,15,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,15,1,5, ORANGE.to_333());
        matrix.fillRect(25,15,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,20,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,20,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,20,1,11, ORANGE.to_333());     
        matrix.fillRect(19,20,1,11, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 
        break;

case 10:
//top line
        matrix.fillRect(12,11,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,12,3,1, ORANGE.to_333());
        matrix.fillRect(19,12,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,13,3,1, ORANGE.to_333());
        matrix.fillRect(21,13,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,14,2,1, ORANGE.to_333());
        matrix.fillRect(23,14,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,15,2,1, ORANGE.to_333());
        matrix.fillRect(24,15,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,15,1,5, ORANGE.to_333());
        matrix.fillRect(25,15,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,20,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,20,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,20,1,11, ORANGE.to_333());     
        matrix.fillRect(19,20,1,11, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 

//BOOM !!!
//B
        matrix.fillRect(9,8,3,1, DAMPWHITE.to_333());
        matrix.fillRect(9,8,1,5, DAMPWHITE.to_333());
        matrix.fillRect(9,6,3,1, DAMPWHITE.to_333());
        matrix.fillRect(9,4,3,1, DAMPWHITE.to_333());
        matrix.fillRect(12,5,1,1, DAMPWHITE.to_333());
        matrix.fillRect(12,7,1,1, DAMPWHITE.to_333());

//O
        matrix.fillRect(15,4,3,1, DAMPWHITE.to_333());
        matrix.fillRect(15,4,1,5, DAMPWHITE.to_333());
        matrix.fillRect(15,8,3,1, DAMPWHITE.to_333());
        matrix.fillRect(17,4,1,5, DAMPWHITE.to_333());

case 11:

//top line
        matrix.fillRect(12,11,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,12,3,1, ORANGE.to_333());
        matrix.fillRect(19,12,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,13,3,1, ORANGE.to_333());
        matrix.fillRect(21,13,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,14,2,1, ORANGE.to_333());
        matrix.fillRect(23,14,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,15,2,1, ORANGE.to_333());
        matrix.fillRect(24,15,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,15,1,5, ORANGE.to_333());
        matrix.fillRect(25,15,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,20,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,20,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,20,1,11, ORANGE.to_333());     
        matrix.fillRect(19,20,1,11, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 

//BOOM !!!
//B
        matrix.fillRect(9,8,3,1, DAMPWHITE.to_333());
        matrix.fillRect(9,8,1,5, DAMPWHITE.to_333());
        matrix.fillRect(9,6,3,1, DAMPWHITE.to_333());
        matrix.fillRect(9,4,3,1, DAMPWHITE.to_333());
        matrix.fillRect(12,5,1,1, DAMPWHITE.to_333());
        matrix.fillRect(12,7,1,1, DAMPWHITE.to_333());

//O
        matrix.fillRect(15,4,3,1, DAMPWHITE.to_333());
        matrix.fillRect(15,4,1,5, DAMPWHITE.to_333());
        matrix.fillRect(15,8,3,1, DAMPWHITE.to_333());
        matrix.fillRect(17,4,1,5, DAMPWHITE.to_333());

//O
        matrix.fillRect(20,4,3,1, DAMPWHITE.to_333());
        matrix.fillRect(20,4,1,5, DAMPWHITE.to_333());
        matrix.fillRect(20,8,3,1, DAMPWHITE.to_333());
        matrix.fillRect(22,4,1,5, DAMPWHITE.to_333());

//M
        matrix.fillRect(24,5,1,4, DAMPWHITE.to_333());
        matrix.fillRect(26,5,1,3, DAMPWHITE.to_333());
        matrix.fillRect(28,5,1,4, DAMPWHITE.to_333());
        matrix.fillRect(25,4,1,1, DAMPWHITE.to_333());
        matrix.fillRect(27,4,1,1, DAMPWHITE.to_333());

case 12:

//top line
        matrix.fillRect(12,11,8,1, ORANGE.to_333());
//second line (L, R)       
        matrix.fillRect(10,12,3,1, ORANGE.to_333());
        matrix.fillRect(19,12,3,1, ORANGE.to_333());
//third line (L, R)       
        matrix.fillRect(8,13,3,1, ORANGE.to_333());
        matrix.fillRect(21,13,3,1, ORANGE.to_333()); 
//fourth line (L, R)       
        matrix.fillRect(7,14,2,1, ORANGE.to_333());
        matrix.fillRect(23,14,2,1, ORANGE.to_333());
//fifth line (L, R)       
        matrix.fillRect(6,15,2,1, ORANGE.to_333());
        matrix.fillRect(24,15,2,1, ORANGE.to_333());
//first lines down (L, R)       
        matrix.fillRect(6,15,1,5, ORANGE.to_333());
        matrix.fillRect(25,15,1,5, ORANGE.to_333());
//sixth line across (L, R)       
        matrix.fillRect(23,20,2,1, ORANGE.to_333());
//Big Line across 1    
        matrix.fillRect(7,20,16,1, ORANGE.to_333());
//2nd lines down L,R  
        matrix.fillRect(12,20,1,11, ORANGE.to_333());     
        matrix.fillRect(19,20,1,11, ORANGE.to_333());
//Big Line across 2
        matrix.fillRect(12,31,8,1, ORANGE.to_333()); 

//BOOM !!!
//B
        matrix.fillRect(9,8,3,1, DAMPWHITE.to_333());
        matrix.fillRect(9,8,1,5, DAMPWHITE.to_333());
        matrix.fillRect(9,6,3,1, DAMPWHITE.to_333());
        matrix.fillRect(9,4,3,1, DAMPWHITE.to_333());
        matrix.fillRect(12,5,1,1, DAMPWHITE.to_333());
        matrix.fillRect(12,7,1,1, DAMPWHITE.to_333());

//O
        matrix.fillRect(15,4,3,1, DAMPWHITE.to_333());
        matrix.fillRect(15,4,1,5, DAMPWHITE.to_333());
        matrix.fillRect(15,8,3,1, DAMPWHITE.to_333());
        matrix.fillRect(17,4,1,5, DAMPWHITE.to_333());

//O
        matrix.fillRect(20,4,3,1, DAMPWHITE.to_333());
        matrix.fillRect(20,4,1,5, DAMPWHITE.to_333());
        matrix.fillRect(20,8,3,1, DAMPWHITE.to_333());
        matrix.fillRect(22,4,1,5, DAMPWHITE.to_333());

//M
        matrix.fillRect(24,5,1,4, DAMPWHITE.to_333());
        matrix.fillRect(26,5,1,3, DAMPWHITE.to_333());
        matrix.fillRect(28,5,1,4, DAMPWHITE.to_333());
        matrix.fillRect(25,4,1,1, DAMPWHITE.to_333());
        matrix.fillRect(27,4,1,1, DAMPWHITE.to_333());
        
//!     
        matrix.fillRect(32,3,2,4, DAMPWHITE.to_333());
        matrix.fillRect(32,8,2,1, DAMPWHITE.to_333());
      }
  }
