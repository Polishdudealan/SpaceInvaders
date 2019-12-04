#pragma once 

#include "Color.h"
#include "Sprite.h"


#ifndef LIBRARIES
  #define LIBRARIES
  #include <gamma.h>
  #include <RGBmatrixPanel.h>
  #include <Adafruit_GFX.h>
#endif

class Powerups: public Sprites {
  public:
    Powerups():
    // powerup->pup
    void draw(RGBmatrixPanel& matrix);
    


  private:
    void draw__pup_with_rgb(Color color, RGBmatrixPanel& matrix);
    
  
}
