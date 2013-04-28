//GameWorld.cpp
//created 4/21/13
//C++ file to accompany GameWorld.h
//handle the animation of the game, and the stats about levels, health, and other playing-related things

#include "GameWorld.h"

// GameWorld::GameWorld(){}


GameWorld::GameWorld(GameMaster* gameMaster), gameAnimationScreen(gameMaster)
{
  std::cout << "Debug GameWorld.cpp Line: 8 - GameWorld Constructor start\n" << std::endl;


	// Initialize stats

  // GameAnimation tempGameAnimation(gameMaster);

  // gameAnimationScreen = tempGameAnimation;

	tokensInProgram = 0;
	livesLeft       = 3;
	scoreTotal      = 0;

  std::cout << "Debug GameWorld.cpp Line: 8 - GameWorld Constructor end\n" << std::endl;

}


void GameWorld::step() {
  gameAnimationScreen.step();
  cout << "Step from GameWorld" << endl;
}


void GameWorld::jump() {
  gameAnimationScreen.jump();
  cout << "Jump from GameWorld" << endl;
}

void GameWorld::turn() {
  gameAnimationScreen.turn();
  cout << "Turn from GameWorld" << endl;
}

void GameWorld::kick() {
  gameAnimationScreen.kick();
  cout << "Kick from GameWorld" << endl;
}


GameStats GameWorld::getStatsFromProgram() {
  cout << "Stats and stuff" << endl; 
}

void GameWorld::updateScreen(SDL_Surface * screen)
{
  gameAnimationScreen.updateScreen(screen);
}