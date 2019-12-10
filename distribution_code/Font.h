#pragma once
#include "Signal.h"
#include "Constants.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

//takes in the number to print and coordinate
namespace Font{
    static void printCharacter(int number, int x_start, int y_start, uint16_t color, Signal & matrix){

      switch(number) {
      case 0:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 0, 1, 5, color);
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, color);
        break;
      case 1:
        matrix.drawPixel(x_start + 0, y_start + 1, color);
        matrix.fillRect(x_start + 1, y_start + 0, 1, 5, color);
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, color);
        break;
      case 2:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 2, 1, 3, color);
        matrix.fillRect(x_start + 2, y_start + 0, 1, 3, color);
        break; 
      case 3:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, color);
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, color);
        break;
      case 4:
        matrix.fillRect(x_start + 0, y_start + 0, 1, 3, color);
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, color);
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, color);
        break;
      case 5:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 0, 1, 3, color);
        matrix.fillRect(x_start + 2, y_start + 2, 1, 3, color);
        break;
      case 6:
        matrix.fillRect(x_start + 0, y_start + 0, 1, 5, color);
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, color);
        matrix.fillRect(x_start + 2, y_start + 2, 1, 3, color);
        
        break;
      case 7:
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, color);
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, color);
        break;
      case 8:
        matrix.fillRect(x_start + 0, y_start + 0, 1, 5, color);
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, color);
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, color);
        break;
      case 9:
        matrix.fillRect(x_start + 0, y_start + 0, 1, 3, color);
        matrix.fillRect(x_start + 0, y_start + 0, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, color);
        matrix.fillRect(x_start + 0, y_start + 4, 3, 1, color);
        matrix.fillRect(x_start + 2, y_start + 0, 1, 5, color);
        break;
      case 'P':
        matrix.fillRect(x_start + 0, y_start + 0, 1, 5, color);
        matrix.drawPixel(x_start + 1, y_start + 0, color);
        matrix.drawPixel(x_start + 2, y_start + 1, color);
        matrix.drawPixel(x_start + 1, y_start + 2, color);
        break;
      case 'V':
        matrix.fillRect(x_start + 0, y_start + 0, 1, 4, color);
        matrix.fillRect(x_start + 2, y_start + 0, 1, 4, color);
        matrix.drawPixel(x_start + 1, y_start + 4, color);
        break;
      case '-':
        matrix.fillRect(x_start + 0, y_start + 2, 3, 1, color);
        break;
      default:
        ;
      }
  }
};
