#include "Pacman.h"

Pacman::Pacman(int width = 13, int height = 13): Sprite(-14,9,width,height) {}

void Pacman::tick(){
  if (fired && curFrame <= 27){
    curFrame++;
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
    curFrame = 0;
    x = -15;
    y = 9;
    fired = true;    
  }
}

void Pacman::draw(Signal& matrix) {
  if (fired) {
    drawPacman(curFrame, matrix);
  }
}

void Pacman::drawPacman(int frame, Signal& matrix) {
    switch (frame) {
        case 1:
//middle rectangle
        matrix.fillRect(-14,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(-13,11,11,2, YELLOW.to_333());
        matrix.fillRect(-13,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(-12,10,9,1, YELLOW.to_333());
        matrix.fillRect(-12,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(-10,9,5,1, YELLOW.to_333());
        matrix.fillRect(-10,21,5,1, YELLOW.to_333());

    break;
    
    case 2:
//line1 middle to up
        matrix.fillRect(-12,15,5,1, YELLOW.to_333());
        matrix.fillRect(-12,14,7,1, YELLOW.to_333());
        matrix.fillRect(-12,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(-12,16,7,1, YELLOW.to_333());
        matrix.fillRect(-12,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(-11,11,11,2, YELLOW.to_333());
        matrix.fillRect(-10,10,9,1, YELLOW.to_333());
        matrix.fillRect(-8,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(-11,18,11,2, YELLOW.to_333());
        matrix.fillRect(-10,20,9,1, YELLOW.to_333());
        matrix.fillRect(-8,21,5,1, YELLOW.to_333());

break;

        case 3:
//middle rectangle
        matrix.fillRect(-10,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(-9,11,11,2, YELLOW.to_333());
        matrix.fillRect(-9,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(-8,10,9,1, YELLOW.to_333());
        matrix.fillRect(-8,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(-6,9,5,1, YELLOW.to_333());
        matrix.fillRect(-6,21,5,1, YELLOW.to_333());

break;

      case 4:
//line1 middle to up
        matrix.fillRect(-8,15,5,1, YELLOW.to_333());
        matrix.fillRect(-8,14,7,1, YELLOW.to_333());
        matrix.fillRect(-8,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(-8,16,7,1, YELLOW.to_333());
        matrix.fillRect(-8,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(-7,11,11,2, YELLOW.to_333());
        matrix.fillRect(-6,10,9,1, YELLOW.to_333());
        matrix.fillRect(-4,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(-7,18,11,2, YELLOW.to_333());
        matrix.fillRect(-6,20,9,1, YELLOW.to_333());
        matrix.fillRect(-4,21,5,1, YELLOW.to_333());

break;

        case 5:
//middle rectangle
        matrix.fillRect(-6,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(-5,11,11,2, YELLOW.to_333());
        matrix.fillRect(-5,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(-4,10,9,1, YELLOW.to_333());
        matrix.fillRect(-4,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(-2,9,5,1, YELLOW.to_333());
        matrix.fillRect(-2,21,5,1, YELLOW.to_333());

break;

         case 6:
//line1 middle to up
        matrix.fillRect(-8,15,5,1, YELLOW.to_333());
        matrix.fillRect(-8,14,7,1, YELLOW.to_333());
        matrix.fillRect(-8,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(-8,16,7,1, YELLOW.to_333());
        matrix.fillRect(-8,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(-7,11,11,2, YELLOW.to_333());
        matrix.fillRect(-6,10,9,1, YELLOW.to_333());
        matrix.fillRect(-4,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(-7,18,11,2, YELLOW.to_333());
        matrix.fillRect(-6,20,9,1, YELLOW.to_333());
        matrix.fillRect(-4,21,5,1, YELLOW.to_333());
    break;

    case 7:
//middle rectangle
        matrix.fillRect(-2,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(-1,11,11,2, YELLOW.to_333());
        matrix.fillRect(-1,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(0,10,9,1, YELLOW.to_333());
        matrix.fillRect(0,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(2,9,5,1, YELLOW.to_333());
        matrix.fillRect(2,21,5,1, YELLOW.to_333());

break;

case 8:
//middle rectangle
        matrix.fillRect(2,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(3,11,11,2, YELLOW.to_333());
        matrix.fillRect(3,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(4,10,9,1, YELLOW.to_333());
        matrix.fillRect(4,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(6,9,5,1, YELLOW.to_333());
        matrix.fillRect(6,21,5,1, YELLOW.to_333());

break;

case 9:
//line1 middle to up
        matrix.fillRect(0,15,5,1, YELLOW.to_333());
        matrix.fillRect(0,14,7,1, YELLOW.to_333());
        matrix.fillRect(0,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(0,16,7,1, YELLOW.to_333());
        matrix.fillRect(0,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(1,11,11,2, YELLOW.to_333());
        matrix.fillRect(2,10,9,1, YELLOW.to_333());
        matrix.fillRect(4,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(1,18,11,2, YELLOW.to_333());
        matrix.fillRect(2,20,9,1, YELLOW.to_333());
        matrix.fillRect(4,21,5,1, YELLOW.to_333());

        break;

  case 10:
//middle rectangle
        matrix.fillRect(6,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(7,11,11,2, YELLOW.to_333());
        matrix.fillRect(7,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(8,10,9,1, YELLOW.to_333());
        matrix.fillRect(8,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(10,9,5,1, YELLOW.to_333());
        matrix.fillRect(10,21,5,1, YELLOW.to_333());

break;

case 11:
//line1 middle to up
        matrix.fillRect(4,15,5,1, YELLOW.to_333());
        matrix.fillRect(4,14,7,1, YELLOW.to_333());
        matrix.fillRect(4,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(4,16,7,1, YELLOW.to_333());
        matrix.fillRect(4,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(5,11,11,2, YELLOW.to_333());
        matrix.fillRect(6,10,9,1, YELLOW.to_333());
        matrix.fillRect(8,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(5,18,11,2, YELLOW.to_333());
        matrix.fillRect(6,20,9,1, YELLOW.to_333());
        matrix.fillRect(8,21,5,1, YELLOW.to_333());

        break;

        case 12:
//middle rectangle
        matrix.fillRect(10,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(11,11,11,2, YELLOW.to_333());
        matrix.fillRect(11,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(12,10,9,1, YELLOW.to_333());
        matrix.fillRect(12,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(14,9,5,1, YELLOW.to_333());
        matrix.fillRect(14,21,5,1, YELLOW.to_333());

break;

case 13:
//line1 middle to up
        matrix.fillRect(8,15,5,1, YELLOW.to_333());
        matrix.fillRect(8,14,7,1, YELLOW.to_333());
        matrix.fillRect(8,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(8,16,7,1, YELLOW.to_333());
        matrix.fillRect(8,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(9,11,11,2, YELLOW.to_333());
        matrix.fillRect(10,10,9,1, YELLOW.to_333());
        matrix.fillRect(12,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(9,18,11,2, YELLOW.to_333());
        matrix.fillRect(10,20,9,1, YELLOW.to_333());
        matrix.fillRect(12,21,5,1, YELLOW.to_333());

        break;

        case 14:
//middle rectangle
        matrix.fillRect(14,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(15,11,11,2, YELLOW.to_333());
        matrix.fillRect(15,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(16,10,9,1, YELLOW.to_333());
        matrix.fillRect(16,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(18,9,5,1, YELLOW.to_333());
        matrix.fillRect(18,21,5,1, YELLOW.to_333());

break;

case 15:
//line1 middle to up
        matrix.fillRect(12,15,5,1, YELLOW.to_333());
        matrix.fillRect(12,14,7,1, YELLOW.to_333());
        matrix.fillRect(12,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(12,16,7,1, YELLOW.to_333());
        matrix.fillRect(12,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(13,11,11,2, YELLOW.to_333());
        matrix.fillRect(14,10,9,1, YELLOW.to_333());
        matrix.fillRect(16,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(13,18,11,2, YELLOW.to_333());
        matrix.fillRect(14,20,9,1, YELLOW.to_333());
        matrix.fillRect(16,21,5,1, YELLOW.to_333());

        break;

  case 16:
//middle rectangle
        matrix.fillRect(18,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(19,11,11,2, YELLOW.to_333());
        matrix.fillRect(19,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(20,10,9,1, YELLOW.to_333());
        matrix.fillRect(20,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(22,9,5,1, YELLOW.to_333());
        matrix.fillRect(22,21,5,1, YELLOW.to_333());

break;

case 17:
//line1 middle to up
        matrix.fillRect(16,15,5,1, YELLOW.to_333());
        matrix.fillRect(16,14,7,1, YELLOW.to_333());
        matrix.fillRect(16,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(16,16,7,1, YELLOW.to_333());
        matrix.fillRect(16,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(17,11,11,2, YELLOW.to_333());
        matrix.fillRect(18,10,9,1, YELLOW.to_333());
        matrix.fillRect(20,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(17,18,11,2, YELLOW.to_333());
        matrix.fillRect(18,20,9,1, YELLOW.to_333());
        matrix.fillRect(20,21,5,1, YELLOW.to_333());

        break;

case 18:
//middle rectangle
        matrix.fillRect(22,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(23,11,11,2, YELLOW.to_333());
        matrix.fillRect(23,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(24,10,9,1, YELLOW.to_333());
        matrix.fillRect(24,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(26,9,5,1, YELLOW.to_333());
        matrix.fillRect(26,21,5,1, YELLOW.to_333());

break;

case 19:
//line1 middle to up
        matrix.fillRect(20,15,5,1, YELLOW.to_333());
        matrix.fillRect(20,14,7,1, YELLOW.to_333());
        matrix.fillRect(20,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(20,16,7,1, YELLOW.to_333());
        matrix.fillRect(20,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(21,11,11,2, YELLOW.to_333());
        matrix.fillRect(22,10,9,1, YELLOW.to_333());
        matrix.fillRect(24,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(21,18,11,2, YELLOW.to_333());
        matrix.fillRect(22,20,9,1, YELLOW.to_333());
        matrix.fillRect(24,21,5,1, YELLOW.to_333());

        break;

        case 20:
//middle rectangle
        matrix.fillRect(26,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(27,11,11,2, YELLOW.to_333());
        matrix.fillRect(27,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(28,10,9,1, YELLOW.to_333());
        matrix.fillRect(28,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(30,9,5,1, YELLOW.to_333());
        matrix.fillRect(30,21,5,1, YELLOW.to_333());

break;

case 21:
//line1 middle to up
        matrix.fillRect(24,15,5,1, YELLOW.to_333());
        matrix.fillRect(24,14,7,1, YELLOW.to_333());
        matrix.fillRect(24,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(24,16,7,1, YELLOW.to_333());
        matrix.fillRect(24,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(25,11,11,2, YELLOW.to_333());
        matrix.fillRect(26,10,9,1, YELLOW.to_333());
        matrix.fillRect(28,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(25,18,11,2, YELLOW.to_333());
        matrix.fillRect(26,20,9,1, YELLOW.to_333());
        matrix.fillRect(28,21,5,1, YELLOW.to_333());

        break;
case 22:
        //middle rectangle
        matrix.fillRect(30,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(31,11,11,2, YELLOW.to_333());
        matrix.fillRect(31,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(32,10,9,1, YELLOW.to_333());
        matrix.fillRect(32,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(34,9,5,1, YELLOW.to_333());
        matrix.fillRect(34,21,5,1, YELLOW.to_333());

break;

case 23:
//line1 middle to up
        matrix.fillRect(28,15,5,1, YELLOW.to_333());
        matrix.fillRect(28,14,7,1, YELLOW.to_333());
        matrix.fillRect(28,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(28,16,7,1, YELLOW.to_333());
        matrix.fillRect(28,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(29,11,11,2, YELLOW.to_333());
        matrix.fillRect(30,10,9,1, YELLOW.to_333());
        matrix.fillRect(32,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(29,18,11,2, YELLOW.to_333());
        matrix.fillRect(30,20,9,1, YELLOW.to_333());
        matrix.fillRect(32,21,5,1, YELLOW.to_333());

        break;

        case 24:
        //middle rectangle
        matrix.fillRect(34,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(35,11,11,2, YELLOW.to_333());
        matrix.fillRect(35,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(36,10,9,1, YELLOW.to_333());
        matrix.fillRect(36,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(38,9,5,1, YELLOW.to_333());
        matrix.fillRect(38,21,5,1, YELLOW.to_333());

break;

case 25:
//line1 middle to up
        matrix.fillRect(32,15,5,1, YELLOW.to_333());
        matrix.fillRect(32,14,7,1, YELLOW.to_333());
        matrix.fillRect(32,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(32,16,7,1, YELLOW.to_333());
        matrix.fillRect(32,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(33,11,11,2, YELLOW.to_333());
        matrix.fillRect(34,10,9,1, YELLOW.to_333());
        matrix.fillRect(36,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(33,18,11,2, YELLOW.to_333());
        matrix.fillRect(34,20,9,1, YELLOW.to_333());
        matrix.fillRect(36,21,5,1, YELLOW.to_333());

        break;

        case 26:
        //middle rectangle
        matrix.fillRect(38,13,13,5, YELLOW.to_333());
//next rectangles (1) (Up, Down)
        matrix.fillRect(39,11,11,2, YELLOW.to_333());
        matrix.fillRect(39,18,11,2, YELLOW.to_333());
//next rectangles (2) (Up, Down)
        matrix.fillRect(40,10,9,1, YELLOW.to_333());
        matrix.fillRect(40,20,9,1, YELLOW.to_333());
//last rectangles (3) (Up, Down)
        matrix.fillRect(42,9,5,1, YELLOW.to_333());
        matrix.fillRect(42,21,5,1, YELLOW.to_333());

break;

case 27:
//line1 middle to up
        matrix.fillRect(36,15,5,1, YELLOW.to_333());
        matrix.fillRect(36,14,7,1, YELLOW.to_333());
        matrix.fillRect(36,13,10,1, YELLOW.to_333());
//line 1 down to middle thing
        matrix.fillRect(36,16,7,1, YELLOW.to_333());
        matrix.fillRect(36,17,10,1, YELLOW.to_333());
//other lines top
        matrix.fillRect(37,11,11,2, YELLOW.to_333());
        matrix.fillRect(38,10,9,1, YELLOW.to_333());
        matrix.fillRect(40,9,5,1, YELLOW.to_333());
//other lines bottom
        matrix.fillRect(37,18,11,2, YELLOW.to_333());
        matrix.fillRect(38,20,9,1, YELLOW.to_333());
        matrix.fillRect(40,21,5,1, YELLOW.to_333());

        break;

}
}
