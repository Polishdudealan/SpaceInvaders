#pragma once

#include "Color.h"
#include "Sprite.h"

#ifndef LIBRARIES
  #define LIBRARIES
  #include <gamma.h>
  #include <RGBmatrixPanel.h>
  #include <Adafruit_GFX.h>
#endif

class Player : public Sprite {
  public:
    Player();
    
    // getters
    int getLives() const;
    
    // setter
    void setX(int xArg);

    //reset lives upon restarting gamme
    void resetLives();
    
    // Modifies: lives
    void die();

    // Modifies: lives for powerup
    void lives1up();

    //draws the space invader on matrix
    void draw(RGBmatrixPanel& matrix);

   

  private:
    int lives;
     
    // sets private data members x and y to initial values
    void initialize(int x_arg, int y_arg);
    void draw_with_rgb(Color color, RGBmatrixPanel& matrix);
    
};
