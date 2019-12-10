#pragma once
#include "Signal.h"
#include "Color.h"


namespace Constants { 
  const Color BLACK(0, 0, 0);
  const Color RED(4, 0, 0);
  const Color ORANGE(6, 1, 0);
  const Color YELLOW(4, 4, 0);
  const Color GREEN(0, 4, 0);
  const Color BLUE(0, 0, 4);
  const Color PURPLE(1, 0, 2);
  const Color WHITE(4, 4, 4);
  const Color LIME(2, 4, 0);
  const Color AQUA(0, 4, 4);
  const Color DAMPWHITE(1, 1, 1);
  const Color DAMPBLUE(0, 0, 2);
  const Color DAMPRED(2, 0, 0);
  
  // define the wiring of the inputs

  const int POTENTIOMETER1_PIN_NUMBER = A14;
  const int POTENTIOMETER2_PIN_NUMBER = A15 ;

  const int BUTTON1_PIN_NUMBER = 35;
  const int BUTTON2_PIN_NUMBER = 37;
  const int BUTTON3_PIN_NUMBER = 39;
  const int BUTTON4_PIN_NUMBER = 41;
    
  //constants to determine game speed
  const int INVADER_DELAY = 30;
  const int POWERUP_DELAY = 9;

  //number of balls for each player
  const int NUM_PLAYER_BALLS = 8;
  
  const int LEVEL_DATA[4][2][8] = 
    {{{1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}},
    {{1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1}},
    {{1, 2, 3, 4, 5, 1, 2, 3}, {4, 5, 1, 2, 3, 4, 5, 1}},
    {{5, 4, 5, 4, 5, 4, 5, 4}, {2, 3, 2, 3, 2, 3, 2, 3}}};

  enum PowerupType {LIFE, RAPID_FIRE, BOMB_SHOT, NONE};
  enum BallType {INVADER, STANDARD, BOMB};
  const int NUM_P_TYPES = 3;
  inline Color p_color(PowerupType type) {
    switch (type) {
      case LIFE:
        return RED;
        break;
      case RAPID_FIRE:
        return AQUA; //wen plotnick said to use this color, citing him as a source, only for this
        break;
      case BOMB_SHOT:
        return YELLOW;
        break;
      case NONE:
        return GREEN;
        break;
      default:
        return BLACK;
    }
  }

};
