#pragma once 

#include "Color.h"
#include "Sprite.h"

#ifndef LIBRARIES
  #define LIBRARIES
  #include <gamma.h>
  #include <RGBmatrixPanel.h>
  #include <Adafruit_GFX.h>
#endif

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

class Powerups : public Sprite {
  public:
    Powerups();
    // powerup->pup
    void draw(RGBmatrixPanel& matrix);
    void move();
    bool check_active();
    void deactivate();


  private:
    void draw__pup_with_rgb(Color color, RGBmatrixPanel& matrix);
    Color p_color(PowerupType power);
    bool active;
     
};
