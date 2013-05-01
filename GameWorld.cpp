/*
  GameWorld.h
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
 
  Handles the animation of the game, and the stats about levels, health, and other playing-related things
  Composed classes:
    GameAnimation - the actual graphical implementation of the level
 */

#include "GameWorld.h"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}


GameWorld::GameWorld(GameMaster* gameMaster): gameAnimationScreen(gameMaster)
{
	// Initialize stats - NOT USED
	tokensInProgram = 0;
	livesLeft       = 3;
	scoreTotal      = 0;
}


void GameWorld::step()
{
	gameAnimationScreen.step();
}


void GameWorld::jump()
{
	gameAnimationScreen.jump();
}

void GameWorld::turn()
{
	gameAnimationScreen.turn();
}

void GameWorld::kick()
{
	gameAnimationScreen.kick();
}


//GameStats GameWorld::getStatsFromProgram() {}  //NOT IMPLEMENTED

void GameWorld::updateScreen(SDL_Surface * screen)
{
	gameAnimationScreen.updateScreen(screen);
}