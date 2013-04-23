#include "GameAnimation.h"

GameAnimation::GameAnimation(){}

GameAnimation::GameAnimation(GameMaster* theGameMaster) {

  background = loadImage("NYC.jpg");
  backRect.x = 0;
  backRect.y = 0;
  backRect.width = background.width;
  backRect.height = background.height;
  gameMasterPointer = theGameMaster;
  
}

void GameAnimation::step() {
  
  mario.status = MARIO_STEP; 
  gameMasterPointer->updateScreen();
  SDL_Delay(50);
  backRect.x -= 50; 
  gameMasterPointer->updateScreen();
  SDL_Delay(50);
  mario.status = MARIO_STAND; 
  gameMasterPointer->updateScreen();

}

void GameAnimation::jump() {
  
  mario.status = MARIO_JUMP;
  mario.marioRect.y -= 50;
  gameMasterPointer->updateScreen();
  SDL_Delay(100);
  mario.marioRect.y -= 50;
  backRect.x -= 50;
  gameMasterPointer->updateScreen();
  SDL_Delay(100);
  mario.marioRect.y += 50;
  backRect.x -= 50;
  gameMasterPointer->updateScreen();
  SDL_Delay(100);
  mario.marioRect.y += 50;
  mario.status = MARIO_STAND;
  gameMasterPointer->updateScreen();
  SDL_Delay(100);

}

void updateScreen(SDL_Surface* screen)
{
	mario.show(screen);
	SDL_BlitSurface( background, NULL, screen, &backRect);
}


void GameAnimation::kick() {

	mario.status = MARIO_KICK;
	gameMasterPointer->updateScreen();
	SDL_Delay(100);
	mario.status = MARIO_STAND; 
	gameMasterPointer->updateScreen();

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
