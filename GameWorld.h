/*
 GameWorld.h
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh
 
 **Description of functionality**
 
 */

#ifndef GAME_WORLD
#define GAME_WORLD

#include <iostream>

//#include "GameStats.h"
#include "GameAnimation.h" // Daniel's class

using namespace std;

class GameWorld
{
  
public:
	GameWorld();
	
	void step();
	void jump();
	void turn();
	void kick();
	//character actions
  
	//GameStats getStatsFromProgram();
  
private:
  
	GameAnimation gameAnimationScreen;
  
	int tokensInProgram;
	int livesLeft;
	int scoreTotal;
	
};

#endif // defined GAME_WORLD