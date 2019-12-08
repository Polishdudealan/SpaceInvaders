#pragma once
#include "Signal.h"
#include "Sprite.h"
#include "Color.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

class Invader : public Sprite {
  public:
    // Constructor, this functions as default
    Invader(int x_arg = 0, int y_arg = 0, int strength_arg = 0, bool dropsPUp = false, int width = 4, int height = 4);
    
    // sets values for private data members
    void initialize(int x_arg, int y_arg, int strength_arg);

    //getters
    int getStrength() const;

    // Moves the Invader down the screen by one row
    // Modifies: y
    void move();
    
    // draws the Invader if its strength is greater than 0
    // calls: draw_with_rgb
    void draw(Signal& matrix);
    
    // Invader is hit by a Cannonball.
    // Modifies: strength
    void hit();

    //returns whether this invader drops a powerup
    bool drops();

  private:
    int strength;
    int ballCycle;
    bool dropsPUp;
    
    // draws the Invader
    void draw_with_rgb(Color body_color, Color eye_color, Signal& matrix);
    
    //converts numbers to space invader colors for easy use with strength color setting
    Color num_to_color(int);
};
