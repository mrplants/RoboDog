#include "GameAnimation.h"

void GameAnimation::step() {
  
  Mario.status = MARIO_STEP; 
  Background.x -= 50; 

}

void GameAnimation::jump() {

  Mario.status = MARIO_JUMP;
  Mario.y -= 50;
  Backround.x -= 50;

}

void GameAnimation::kick() {

  Mario.status = MARIO_KICK;

}

void GameAnimation::turn() {

  Mario.status = MARIO_TURN;

}

			  
