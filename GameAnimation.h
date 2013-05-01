/*
  GameAnimation.h
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  Implements the graphics corresponding to the code the user input
  Composed classes:
    Mario - the character, RoboDog himself
  */

#ifndef GAMEANIMATION_H
#define GAMEANIMATION_H

#include "constants.h"
#include "SDL_Program.h"
#include "Mario.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>

class GameMaster;

class GameAnimation : public SDL_Program {
 public:

  GameAnimation();
  ~GameAnimation();

  GameAnimation(GameMaster*);

  // define clip locations for the background image                          
  void clip_background();
  
  //player commands
  void step();
  void jump();
  void turn();
  void kick();

  // clean up function
  virtual void cleanUp();
  
  // update the screen
  void updateScreen(SDL_Surface*);

 private:

  // background surface
  SDL_Surface *background;
  
  // rectangle where background is blitted
  SDL_Rect backRect;

  // current scene of background being shown
  int scene;

  // congratulatory surface
  SDL_Surface *congratulatory;

  // loser surface
  SDL_Surface *loser;

  // enemy surface
  SDL_Surface *enemy;

  // rectangle where enemy is blitted
  SDL_Rect enemyRect;

  // checks whether or not Mario killed the enemy
  void didKill();

  // checks wheter or not the user has lost
  void didLose();

  // whether or not Mario killed enemy
  bool killedEnemy;

  // whether or not the user has lost
  bool lost;

  // areas of background sheet
  SDL_Rect backClips[ (LEVEL_LENGTH / GAME_WORLD_W * 24) ];

  // instance of Mario
  Mario mario;

  // pointer to game master
  GameMaster *gameMasterPointer;

};

#endif // defined GAMEANIMATION_H
