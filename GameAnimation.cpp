#include "GameAnimation.h"

GameAnimation::GameAnimation() {

	background = loadImage("NYC.jpg");

}

void GameAnimation::step() {
  
  mario.status = MARIO_STEP; 
  backRect.x -= 50; 
  SDL_Delay(100);

}

void GameAnimation::jump() {

  mario.status = MARIO_JUMP;
  mario.marioRect.y -= 50;
  backRect.x -= 50;
  SDL_Delay(100);

}

void GameAnimation::kick() {

	if (mario.status == MARIO_STEP)
	{
		mario.status = MARIO_KICK;
		SDL_Delay(100);
		mario.status = MARIO_STEP; 
	} else
	{

	}

}

void GameAnimation::turn() {

  mario.status = MARIO_TURN;

  #warning this needs to be worked on because all the other images return to MARIO_STEP instead of MARIO_TURN

}

void GameAnimation::cleanUp()
{
	mario.cleanUp();
	SDL_FreeSurface(background);
}