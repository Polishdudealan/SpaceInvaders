#include "Gamemode.h"
#include "Signal.h"
#include "Player.h"
#include "Powerups.h"
#include "Cannonball.h"
#include "Invader.h"
#include "Pacman.h"

#ifndef FONT
  #define FONT
  #include "Font.h"
#endif


#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

class Game2P : public Gamemode {
  public:
    Game2P();
      
    // sets up game
    void setupGame();
      

    // runs game
    void update(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed);

  private:
    // game constant for the number of Invaders in the game
    static const int NUM_ENEMIES = 24;

    //game constant for number of enemy balls possible
    static const int NUM_ENEMY_BALLS = 10;
  
    //game constant for the number of players in the game
    static const int NUM_PLAYERS = 2;

    //game constant for number of powerups
    static const int NUM_POWERUPS = 1;

    static const int NUM_PACMEN = 1;

    //total sprites
    static const int NUM_SPRITES = NUM_ENEMIES + NUM_ENEMY_BALLS + NUM_PLAYERS*NUM_PLAYER_BALLS + NUM_PACMEN + NUM_PLAYERS + NUM_POWERUPS;
    
    //our class for sending board info to the unos
    Signal matrix;

    int level;
    unsigned long time;
    int numUpdates;
    int layers;
    int currentLayer;
    bool playersCollided = false;
    
    // defines player score and initializes to 0
    int player1Score = 0;
    int player2Score = 0;

    //****** Sprites ********
    Player player1{BLUE};
    Player player2{RED};
    Invader enemies[NUM_ENEMIES];
    Cannonball enemyBalls[NUM_ENEMY_BALLS];
    Powerups powerup;
    Pacman pacman;
    Sprite* updatableSprites[NUM_SPRITES];


    //***** Helper Functions
    // check if Player defeated all Invaders in current level
    bool level_cleared();

    //checks if the first layer of invaders is clear
    bool layerCleared(int layer);

    // set up a level
    void reset_level();

    //return proper cannonball
    Cannonball* getEnemyCannonball();
    
    
    //********** update functions **********
    //moves all sprites in game
    void moveUpdate();

    //checks inputs from the user
    void inputUpdate(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed);

    //checks to see if there are any collisions which are important to gameplay
    void checkCollisions();

    //redraws all sprites that have been updated
    void redrawSprites();

  
    //********** printer functions **********
    // displays Level
    void print_level(int level);
    
    // displays number of lives
    void print_lives(int lives, int lives2);
    
    // displays "game over"
    void game_over();

    // displays scoreboard
    void score_board(int score1Number, int score2Number);
};
