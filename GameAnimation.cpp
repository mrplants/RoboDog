#include "GameAnimation.h"

GameAnimation::GameAnimation(GameMaster* theGameMaster) {

  background = loadImage("NYC.jpg");
  gameMaster = theGameMaster;
  
}

void GameAnimation::step() {
  
  mario.status = MARIO_STEP; 
  gameMaster->updateScreen();
  SDL_Delay(50);
  backRect.x -= 50; 
  gameMaster->updateScreen();
  SDL_Delay(50);
  mario.status = MARIO_STAND; 
  gameMaster->updateScreen();

}

void GameAnimation::jump() {
  
  mario.status = MARIO_JUMP;
  mario.marioRect.y -= 50;
  gameMaster->updateScreen();
  SDL_Delay(100);
  mario.marioRect.y -= 50;
  backRect.x -= 50;
  gameMaster->updateScreen();
  SDL_Delay(100);
  mario.marioRect.y += 50;
  backRect.x -= 50;
  gameMaster->updateScreen();
  SDL_Delay(100);
  mario.marioRect.y += 50;
  mario.status = MARIO_STAND;
  gameMaster->updateScreen();
  SDL_Delay(100);

}

void updateScreen(SDL_Surface* screen)
{
	mario.show(screen);
	#warning still need to blit the background to the screen. !!It needs to scroll!!
}


void GameAnimation::kick() {

	mario.status = MARIO_KICK;
	gameMaster->updateScreen();
	SDL_Delay(100);
	mario.status = MARIO_STAND; 
	gameMaster->updateScreen();

}

void GameAnimation::turn() {
	std::cout << "ERROR: Still need to create the sprite sheet and stuff for reversed orientation of character" << std::endl;
  #warning Still need to create the sprite sheet and stuff for reversed orientation of character
}

void GameAnimation::cleanUp()
{
  mario.cleanUp();
  SDL_FreeSurface(background);
}
