/*
 GameWorld.h
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh
 
 **Description of functionality**
 
 */

#ifndef GAME_WORLD
#define GAME_WORLD

#include <iostream>
#include "GameStats.h"
#include "GameAnimation.h" // Daniel's class
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
 
using namespace std;

class GameMaster;

class GameWorld
{
  
public:
	GameWorld(GameMaster* gameMaster);
	
	void step();
	void jump();
	void turn();
	void kick();
	//character actions
  
	GameStats getStatsFromProgram();
	void updateScreen(SDL_Surface*);
  
private:
  
	GameAnimation gameAnimationScreen;
  
	int tokensInProgram;
	int livesLeft;
	int scoreTotal;
	
};

#endif // defined GAME_WORLD