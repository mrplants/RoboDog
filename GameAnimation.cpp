#include "GameAnimation.h"

GameAnimation::GameAnimation() {

background = load_image  

}

void GameAnimation::step() {
  
  Mario.status = MARIO_STEP; 
  backRect.x -= 50; 

}

void GameAnimation::jump() {

  Mario.status = MARIO_JUMP;
  Mario.marioRect.y -= 50;
  backRect.x -= 50;

}

void GameAnimation::kick() {

  Mario.status = MARIO_KICK;
  

}

void GameAnimation::turn() {

  Mario.status = MARIO_TURN;

}

			  
