#pragma once

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

#include "Signal.h"
#include "Sprite.h"
#include "Color.h" 

using namespace Constants;

class Pacman : public Sprite {
  public:
    Pacman(int width = 13, int height = 13);
        
    // getters
    bool hasBeenFired() const;
    
    // sets private data members
    void fire();
    
    //updates all cannonball information, which depends upon type
    void tick();
    
    // draws the Cannonball, if it is fired
    void draw(Signal& matrix);

  private:
    bool fired;
    int curFrame = 0;

    void drawPacman(int frame, Signal& matrix);

};
