#include "GameAnimation.h"

GameAnimation::GameAnimation() {

background = load_image  

}

void GameAnimation::step() {
  
  mario.status = MARIO_STEP; 
  backRect.x -= 50; 

}

void GameAnimation::jump() {

  mario.status = MARIO_JUMP;
  mario.marioRect.y -= 50;
  backRect.x -= 50;

}

void GameAnimation::kick() {

  mario.status = MARIO_KICK;
  

}

void GameAnimation::turn() {

  mario.status = MARIO_TURN;

}

void GameAnimation::cleanUp()
{
	mario.cleanUp();
	SDL_FreeSurface(background);
}