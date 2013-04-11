#include <iostream>

#include "GameStats.h"
// #include "GameAnimation.h" // Daniel's class

class GameWorld
{
  
  public:
  
    void step();
    void jump();
    void turn();
    void kick();
    //character actions
  
    GameStats getStatsFromProgram();
  
  private:
  
    GameAnimation gameAnimationScreen;
  
    int tokensInProgram;
    int livesLeft;
    int scoreTotal;
    
};
