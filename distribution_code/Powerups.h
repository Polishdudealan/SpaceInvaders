#pragma once 

#include "Color.h"
#include "Sprite.h"
#include "Signal.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

class Powerups : public Sprite {
  public:
    Powerups(int width = 3, int height = 3);
    
    // powerup->pup
    void draw(Signal& matrix);
    
    void move();
    
    bool check_active() const;
    
    void deactivate();

    Constants::PowerupType getType() const;

    void spawn(int x, int y, Constants::PowerupType type);

  private:
    Constants::PowerupType type;
    bool active;     
};
