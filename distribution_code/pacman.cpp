#include "Pacman.h"

Pacman::Pacman(int width = 13, int height = 13): Sprite(-14,9,width,height) {}

void Pacman::tick(){
  if (fired && x < 32){
    x++;
  } else {
    fired = false;
  }
}

bool Pacman::hasBeenFired() const {
  return fired;
}

void Pacman::fire() {
  if (!fired) {
    x = -15;
    y = 9;
    fired = true;    
  }
}

void Pacman::draw(Signal& matrix) {
  if (fired) {
    drawPacman(matrix);
  }
}

void Pacman::drawPacman(Signal& matrix) {
    if (x % 2 == 0) {
        //middle rectangle
        matrix.fillRect(x,13,13,5, YELLOW.to_333());
        //next rectangles (1) (Up, Down)
        matrix.fillRect(x+1,11,11,2, YELLOW.to_333());
        matrix.fillRect(x+1,18,11,2, YELLOW.to_333());
        //next rectangles (2) (Up, Down)
        matrix.fillRect(x+2,10,9,1, YELLOW.to_333());
        matrix.fillRect(x+2,20,9,1, YELLOW.to_333());
        //last rectangles (3) (Up, Down)
        matrix.fillRect(x+4,9,5,1, YELLOW.to_333());
        matrix.fillRect(x+4,21,5,1, YELLOW.to_333());
    } else {
        //line1 middle to up
        matrix.fillRect(x,15,5,1, YELLOW.to_333());
        matrix.fillRect(x,14,7,1, YELLOW.to_333());
        matrix.fillRect(x,13,10,1, YELLOW.to_333());
        //line 1 down to middle thing
        matrix.fillRect(x,16,7,1, YELLOW.to_333());
        matrix.fillRect(x,17,10,1, YELLOW.to_333());
        //other lines top
        matrix.fillRect(x+1,11,11,2, YELLOW.to_333());
        matrix.fillRect(x+2,10,9,1, YELLOW.to_333());
        matrix.fillRect(x+4,9,5,1, YELLOW.to_333());
        //other lines bottom
        matrix.fillRect(x+1,18,11,2, YELLOW.to_333());
        matrix.fillRect(x+2,20,9,1, YELLOW.to_333());
        matrix.fillRect(x+4,21,5,1, YELLOW.to_333());
    }
}
