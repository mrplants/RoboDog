#include "GameAnimation.h"
#include "GameMaster.h"

GameAnimation::GameAnimation() : SDL_Program() {}

GameAnimation::GameAnimation(GameMaster* theGameMaster) : SDL_Program(),mario("Mario.bmp") {

    std::cout << "Debug GameAnimation.cpp Line: 8 - GameAnimation Constructor start\n" << std::endl;


  background = loadImage("NYC.jpg");
  backRect.x = 0;
  backRect.y = 0;
  backRect.w = background->w;
  backRect.h = background->h;
  gameMasterPointer = theGameMaster;

    std::cout << "Debug GameAnimation.cpp Line: 8 - GameAnimation Constructor end\n" << std::endl;

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

void GameAnimation::updateScreen(SDL_Surface* screen)
{
    	SDL_BlitSurface( background, NULL, screen, &backRect);
	mario.show(screen);
}


void GameAnimation::kick() {

	mario.status = MARIO_KICK;
	gameMasterPointer->updateScreen();
	SDL_Delay(100);
	mario.status = MARIO_STAND; 
	gameMasterPointer->updateScreen();

}

void GameAnimation::turn() {
	std::cout << "ERROR: Still need to create the sprite sheet for reversed orientation of character" << std::endl;
  #warning Still need to create the sprite sheet and stuff for reversed orientation of character
}

void GameAnimation::cleanUp()
{
  mario.cleanUp();
  SDL_FreeSurface(background);
}
