/*
  GameWorld.h
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  Handles the animation of the game, and the stats about levels, health, and other playing-related things
  Composed classes:
    GameAnimation - the actual graphical implementation of the level
 */

#ifndef GAME_WORLD
#define GAME_WORLD

#include <iostream>
#include "GameAnimation.h" // Daniel's class
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
 
using namespace std;

class GameMaster;

class GameWorld
{
  
public:
	GameWorld();
	
	~GameWorld();

	GameWorld(GameMaster* gameMaster);
	
	void step();
	void jump();
	void turn();
	void kick();
	//character actions
  
	//GameStats getStatsFromProgram(); //NOT IMPLEMENTED
	void updateScreen(SDL_Surface*);
  
private:
  
	GameAnimation gameAnimationScreen;
  
	int tokensInProgram;
	int livesLeft;
	int scoreTotal;
	
};

#endif // defined GAME_WORLD