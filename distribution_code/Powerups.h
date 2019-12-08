#pragma once 

#include "Color.h"
#include "Sprite.h"
#include "Signal.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

class Powerups : public Sprite {
  public:
    Powerups();
    // powerup->pup
    void draw(Signal& matrix);
    void move();
    bool check_active();
    void deactivate();


  private:
    void draw__pup_with_rgb(Color color, Signal& matrix);
    Color p_color(PowerupType power);
    bool active;
     
};
