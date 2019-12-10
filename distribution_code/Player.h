#pragma once
#include "Signal.h"
#include "Color.h"
#include "Sprite.h"
#include "Cannonball.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

class Player : public Sprite {
  public:
    Player();

    Cannonball balls[NUM_PLAYER_BALLS];
    
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

    //reloads blasters
    void reload();

    //fires a ball
    void fire();

    //fires a special ball determined by powerups
    void specialFire();
    
  private:
    int lives;
    int ballDelay;
    int ballCycle = 0;
    int specialDelay;
    int specialCycle = 0;
    PowerupType powerupAbility;
    BallType specialType;
     
    // sets private data members x and y to initial values
    void initialize(int x_arg, int y_arg);
    void draw_with_rgb(Color color, Signal& matrix);

    //returns the proper ball to use when fire is called
    Cannonball* getPlayerBall();    
};
