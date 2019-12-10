#pragma once
#include "Signal.h"
#include "Constants.h"


//takes in the number to print and coordinate
namespace Font{
    static void printCharacter(int number, int x_start, int y_start, Signal & matrix){

      switch(number) {
      case 0:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 0, 1, 5, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, DAMPWHITE.to_333());
        break;
      case 1:
        matrix.drawPixel(x_start + 0, y_start + 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 1, y_start + 0, 1, 5, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, DAMPWHITE.to_333());
        break;
      case 2:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 2, 1, 3, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 0, 1, 3, DAMPWHITE.to_333());
        break; 
      case 3:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, DAMPWHITE.to_333());
        break;
      case 4:
        matrix.fillRect(x_start + 0, y_start + 0, 1, 3, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, DAMPWHITE.to_333());
        break;
      case 5:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 0, 1, 3, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 2, 1, 3, DAMPWHITE.to_333());
        break;
      case 6:
        matrix.fillRect(x_start + 0, y_start + 0, 1, 5, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 2, 1, 3, DAMPWHITE.to_333());
        
        break;
      case 7:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, DAMPWHITE.to_333());
        break;
      case 8:
        matrix.fillRect(x_start + 0, y_start + 0, 1, 5, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, DAMPWHITE.to_333());
        break;
      case 9:
        matrix.fillRect(x_start + 0, y_start + 0, 1, 3, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, DAMPWHITE.to_333());
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, DAMPWHITE.to_333());
      default:
        ;
      }
  }
};
