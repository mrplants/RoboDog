//GameWorld.cpp
//created 4/21/13
//C++ file to accompany GameWorld.h
//handle the animation of the game, and the stats about levels, health, and other playing-related things

#include "GameWorld.h"

GameWorld::GameWorld() {

	// Initialize stats

	tokensInProgram = 0;
	livesLeft       = 3;
	scoreTotal      = 0;
}


void GameWorld::step() {
  // gameAnimationScreen.step(); or its equivalent	
  gameAnimation.step();
  cout << "Step from GameWorld" << endl;
}


void GameWorld::jump() {
  // gameAnimationScreen.jump(); or its equivalent
  gameAnimation.jump();
  cout << "Jump from GameWorld" << endl;
}

void GameWorld::turn() {
	// gameAnimationScreen.turn(); or its equivalent
  gameAnimation.turn();
  cout << "Turn from GameWorld" << endl;
}

void GameWorld::kick() {
  // gameAnimationScreen.kick(); or its equivalent
  gameAnimation.kick();
  cout << "Kick from GameWorld" << endl;
}

GameWorld::getStatsFromProgram() {
  cout << "Stats and stuff" << endl;  
}



