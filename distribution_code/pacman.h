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
    Pacman(int width = 17, int height = 13);
        
    // getters
    bool hasBeenFired() const;
    
    // sets private data members
    void fire();
    
    //updates all cannonball information, which depends upon type
    void tick();
    
    // draws the Cannonball, if it is fired
    void draw(Signal& matrix);

    //stops pacman mayhem, because if you have cut rate car insurance your car could be in danger from pacmen like these
    void deactivate();
  private:
    bool fired;
    bool alternator = false;
    int curFrame = 0;

    void drawPacman(Signal& matrix);

};
