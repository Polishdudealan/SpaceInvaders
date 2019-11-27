#pragma once

#include "Sprite.h"
#include "Color.h"

class Invader : public Sprite {
  public:
    // Constructor, this functions as default
    Invader(int x_arg = 0, int y_arg = 0, int strength_arg = 0, int height = 4, int width = 4);
    
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
    void draw(RGBmatrixPanel& matrix);
    
    // draws black where the Invader used to be
    // calls: draw_with_rgb
    void erase(RGBmatrixPanel& matrix);
    
    // Invader is hit by a Cannonball.
    // Modifies: strength
    void hit();

  private:
    int strength;
    
    //origin is upper left corner
    int x;
    int y;

    //extending right and down from origin 
    int width;
    int height;
    
    SpriteType type = INVADER;
    
    // draws the Invader
    void draw_with_rgb(Color body_color, Color eye_color, RGBmatrixPanel& matrix);
};
