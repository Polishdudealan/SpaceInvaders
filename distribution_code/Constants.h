#pragma once
#include "Signal.h"
#include "Color.h"


namespace Constants { 
  const Color BLACK(0, 0, 0);
  const Color RED(4, 0, 0);
  const Color MAGENTA(4, 0, 2);
  const Color ORANGE(6, 1, 0);
  const Color YELLOW(4, 4, 0);
  const Color GREEN(0, 4, 0);
  const Color BLUE(0, 0, 4);
  const Color PURPLE(1, 0, 2);
  const Color WHITE(4, 4, 4);
  const Color LIME(2, 4, 0);
  const Color AQUA(0, 4, 4);
  const Color DAMPWHITE(1, 1, 1);
  const Color DAMPAQUA(0, 2, 2);
  const Color DAMPBLUE(0, 0, 2);
  const Color DAMPRED(2, 0, 0);
  
  // define the wiring of the inputs
  const int PIEZOPIN = 36;

  const int POTENTIOMETER1_PIN_NUMBER = A14;
  const int POTENTIOMETER2_PIN_NUMBER = A15 ;

  //game speed (30 is a good value)
  static int boardComputationDelay = 20;
  
  const int BUTTON1_PIN_NUMBER = 26;
  const int BUTTON2_PIN_NUMBER = 28;
  const int BUTTON3_PIN_NUMBER = 30;
  const int BUTTON4_PIN_NUMBER = 32;
    
  //constants to determine game speed
  const int INVADER_DELAY = 30;
  const int POWERUP_DELAY = 5;

  //Determines how often invader shoots, lower numbers are more often
  const int INVADER_SHOOT_PROBABILITY = 100;

  //number of balls for each player
  const int NUM_PLAYER_BALLS = 8;

  const int NUM_SCRIPTED_LEVELS = 26;
  const int LEVEL_DATA[NUM_SCRIPTED_LEVELS][3][8] = 
   {{{1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}, 
    {{1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1}, {0, 0, 0, 0, 0, 0, 0, 0}}, 
    {{1, 2, 3, 4, 4, 3, 2, 1}, {0, 1, 2, 3, 3, 2, 1, 0}, {0, 0, 1, 2, 2, 1, 0, 0}}, 
    {{6, 0, 4, 4, 4, 4, 0, 6}, {0, 6, 5, 6, 6, 5, 6, 0}, {0, 0, 6, 0, 0, 6, 0, 0}},
    {{1, 8, 1, 8, 1, 8, 1, 8}, {8, 1, 8, 1, 8, 1, 8, 1}, {0, 0, 0, 0, 0, 0, 0, 0}},
    {{4, 5, 6, 9, 9, 6, 5, 4}, {0, 4, 5, 6, 6, 5, 4, 0}, {0, 0, 4, 5, 5, 4, 0, 0}},
    {{8, 8, 8, 8, 8, 8, 8, 8}, {8, 8, 8, 8, 8, 8, 8, 8}, {8, 8, 8, 8, 8, 8, 8, 8}},
    {{7, 7, 7, 8, 8, 7, 7, 7}, {5, 5, 5, 6, 6, 5, 5, 5}, {3, 3, 3, 3, 3, 3, 3, 3}},
    {{7, 0, 4, 4, 4, 4, 0, 6}, {0, 7, 15, 7, 7, 15, 7, 0}, {7, 0, 7, 0, 0, 7, 0, 7}},
    {{7, 0, 4, 4, 4, 4, 0, 6}, {0, 7, 15, 15, 15, 15, 7, 0}, {7, 0, 7, 0, 0, 7, 0, 7}},
    {{0, 0, 4, 7, 7, 4, 0, 0}, {0, 7, 9, 16, 16, 9, 7, 0}, {7, 0, 12, 0, 0, 12, 0, 7}},
    {{0, 0, 4, 7, 7, 4, 0, 0}, {0, 7, 9, 16, 16, 9, 7, 0}, {7, 0, 12, 0, 0, 12, 0, 7}},
    {{0, 0, 4, 7, 7, 4, 0, 0}, {0, 7, 9, 16, 16, 9, 7, 0}, {7, 0, 12, 0, 0, 12, 0, 7}},
    {{0, 1, 4, 7, 7, 4, 1, 0}, {0, 0, 9, 16, 16, 9, 0, 0}, {0, 0, 12, 18, 18, 12, 0, 0}},
    {{0, 1, 4, 7, 7, 4, 1, 0}, {0, 0, 9, 16, 16, 9, 0, 0}, {0, 0, 0, 20, 20, 0, 0, 0}},
    {{0, 1, 4, 7, 7, 4, 1, 0}, {0, 0, 9, 16, 16, 9, 0, 0}, {0, 0, 0, 20, 20, 0, 0, 0}},
    {{0, 0, 4, 7, 7, 4, 0, 0}, {0, 11, 9, 16, 16, 9, 1, 0}, {0, 12, 0, 20, 20, 0, 12, 0}},
    {{0, 0, 4, 7, 7, 4, 0, 0}, {0, 11, 9, 16, 16, 9, 1, 0}, {0, 12, 0, 20, 20, 0, 12, 0}},
    {{7, 13, 0, 0, 0, 0, 13, 7}, {0, 0, 19, 2, 2, 19, 0, 0}, {21, 12, 0, 0, 0, 0, 12, 21}},
    {{7, 13, 0, 0, 0, 0, 12, 7}, {0, 0, 19, 4, 4, 19, 0, 0}, {25, 12, 0, 0, 0, 0, 12, 21}},
    {{7, 13, 0, 0, 0, 0, 0, 0}, {0, 0, 17, 17, 12, 0, 0, 0}, {0, 0, 0, 0, 0, 21, 12, 21}},
    {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {30, 0, 0, 0, 0, 0, 0, 30}},
    {{7, 13, 0, 0, 0, 0, 0, 0}, {0, 0, 17, 17, 12, 0, 0, 0}, {0, 0, 0, 0, 0, 21, 12, 21}},
    {{7, 0, 0, 0, 0, 0, 12, 17}, {0, 14, 0, 17, 0, 21, 21, 0}, {0, 0, 21, 0, 21, 0, 0, 0}},
    {{7, 7, 0, 0, 0, 0, 7, 7}, {0, 0, 14, 14, 14, 14, 0, 0}, {21, 21, 0, 0, 0, 0, 21, 21}},
    {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 90, 0, 0, 0}}};

    inline Color rainbow(){
      int seed = random(0,5);
      switch (seed) {
        case 0:
          return RED;
          break;
        case 1:
          return ORANGE;
          break;
        case 2:
          return YELLOW;
          break;
        case 3:
          return GREEN;
          break;
        case 4:
          return BLUE;
          break;
        case 5:
          return PURPLE;
          break;
        default:
          return BLACK;
      }
    }

  enum PowerupType {LIFE, RAPID_FIRE, SCATTER_SHOT, BOMB_SHOT, SNIPER, PACMAN, JUGGERNAUGHT, NUKE, NONE};
  const int NUM_P_TYPES = 8;
  inline Color p_color(PowerupType type) {
    switch (type) {
      case LIFE:
        return RED;
      case RAPID_FIRE:
        return AQUA; //wen plotnick said to use this color, citing him as a source, only for this
      case BOMB_SHOT:
        return ORANGE;
      case PACMAN:
        return YELLOW;
      case NUKE:
        return LIME;
      case SNIPER:
        return DAMPWHITE;
      case SCATTER_SHOT:
        return PURPLE;
      case JUGGERNAUGHT:
        return rainbow();
      case NONE:
        return GREEN;
      default:
        return BLACK;
    }
  }
  enum BallType {INVADER, STANDARD, STRONG, BOMB, JUGG, SNIPE};
  inline Color b_color(BallType type){
    switch (type) {
      case STANDARD:
        return RED;
      case STRONG:
        return MAGENTA;
      case INVADER:
        return GREEN;
      case BOMB:
        return ORANGE;
      case SNIPE:
        return DAMPWHITE;
      case JUGG:
        return rainbow();
      default:
        return BLACK;
    }
  }
};
