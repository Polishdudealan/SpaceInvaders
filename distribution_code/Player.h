#pragma once
#include "Signal.h"
#include "Color.h"
#include "Sprite.h"
#include "Cannonball.h"

#include "Constants.h"
using namespace Constants;

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

    //this should be called when there is a collision with a powerup
    void powerup(PowerupType);

    // Modifies: lives when get life powerup
    void lives1up();

    //draws the space invader on matrix
    void draw(Signal& matrix);

    //fires a cannoball
    void fire();

    //reloads the blasters
    void reload();

    //list of cannonballs for player
    Cannonball balls[NUM_BALLS];

  private:
    int lives;
    int ballCycle;
     
    // sets private data members x and y to initial values
    void initialize(int x_arg, int y_arg);
    void draw_with_rgb(Color color, Signal& matrix);

    //returns the proper ball to use when fire is called
    Cannonball* getBall();    

    
};
