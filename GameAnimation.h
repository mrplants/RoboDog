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

  // whether or not Mario killed enemy
  int killedEnemy;

  // areas of background sheet
  SDL_Rect backClips[ (LEVEL_LENGTH / GAME_WORLD_W * 24) ];

  // instance of Mario
  Mario mario;

  // pointer to game master
  GameMaster *gameMasterPointer;

};

#endif // defined GAMEANIMATION_H
