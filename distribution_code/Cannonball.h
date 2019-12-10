#pragma once

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

#include "Signal.h"
#include "Sprite.h"
#include "Color.h" 

using namespace Constants;

class Cannonball : public Sprite {
  public:
    Cannonball(BallType type = STANDARD, int width = 1, int height = 2);
    
    // resets private data members to initial values
    void reset();
    
    // getters
    bool hasBeenFired() const;

    //gets the ball type
    BallType getType();

    //sets what type the ball is
    void setType(BallType type);
    
    // sets private data members
    void fire(int x_arg, int y_arg);
    
    //updates all cannonball information, which depends upon type
    void tick();
    
    // resets private data members to initial values
    void hit();
    
    // draws the Cannonball, if it is fired
    void draw(Signal& matrix);


  private:
    bool fired;
    bool exploding;
    int explodingDuration;
    BallType type;
};
