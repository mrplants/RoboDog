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

  // clip the sprite sheet
  mario.set_clips();

  std::cout << "Debug GameAnimation.cpp Line: 8 - GameAnimation Constructor end\n" << std::endl;

}

void GameAnimation::step() {
  
  mario.status = MARIO_STEP; 
  gameMasterPointer->updateScreen();
  SDL_Delay(1000);
  backRect.x -= MARIO_WIDTH;
  gameMasterPointer->updateScreen();
  SDL_Delay(1000);
  mario.status = MARIO_STAND; 
  gameMasterPointer->updateScreen();

}

void GameAnimation::jump() {

  mario.status = MARIO_JUMP;
  mario.marioRect.y -= MARIO_HEIGHT / 2;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);
  mario.marioRect.y -= MARIO_HEIGHT / 2;
  backRect.x -= MARIO_WIDTH;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);
  mario.marioRect.y += MARIO_HEIGHT / 2;
  backRect.x -= MARIO_WIDTH;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);
  mario.marioRect.y += MARIO_HEIGHT / 2;
  mario.status = MARIO_STAND;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);

}

void GameAnimation::updateScreen(SDL_Surface* screen)
{
  tempRect.x = backRect.x + background->w;
  tempRect.y = backRect.y;
  tempRect.w = background->w;
  tempRect.h = background->h;

  SDL_BlitSurface( background, NULL, screen, &backRect);
  SDL_BlitSurface( background, NULL, screen, &tempRect);
  mario.show(screen);
}


void GameAnimation::kick() {
  mario.status = MARIO_KICK;
  gameMasterPointer->updateScreen();
  SDL_Delay(500);
  mario.status = MARIO_STAND; 
  gameMasterPointer->updateScreen();
  
}

void GameAnimation::turn() {
  mario.status = MARIO_TURN;
  gameMasterPointer->updateScreen();
  SDL_Delay(500);
  mario.status = MARIO_STAND;
  gameMasterPointer->updateScreen();

}

void GameAnimation::cleanUp()
{
  mario.cleanUp();
  SDL_FreeSurface(background);
}
