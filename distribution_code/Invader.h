#pragma once
#include "Signal.h"
#include "Sprite.h"
#include "Color.h"

class Invader : public Sprite {
  public:
    // Constructor, this functions as default
    Invader(int x_arg = 0, int y_arg = 0, int strength_arg = 0, int width = 4, int height = 4);
    
    // sets values for private data members
    void initialize(int x_arg, int y_arg, int strength_arg) {
      x = x_arg;
      y = y_arg;
      strength = strength_arg;
    }

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

  private:
    int strength;
    
    // draws the Invader
    void draw_with_rgb(Color body_color, Color eye_color, Signal& matrix);

    
    //converts numbers to space invader colors for easy use with strength color setting
    Color num_to_color(int);
};
