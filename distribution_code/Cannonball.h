#pragma once

#include "Sprite.h"
#include "Color.h" 

class Cannonball : public Sprite {
  public:
    Cannonball(int width = 1, int height = 2);
    
    // resets private data members to initial values
    void reset();
    
    // getters
    bool hasBeenFired() const;
    
    // sets private data members
    void fire(int x_arg, int y_arg);
    
    // moves the Cannonball and detects if it goes off the screen
    // Modifies: y, fired
    void move();
    
    // resets private data members to initial values
    void hit();
    
    // draws the Cannonball, if it is fired
    void draw(RGBmatrixPanel& matrix);

  private:
    bool fired;
};
