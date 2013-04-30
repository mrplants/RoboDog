#include "GameAnimation.h"
#include "GameMaster.h"


GameAnimation::GameAnimation() : SDL_Program() {}

GameAnimation::~GameAnimation() {
  
  std::cout << "GameAnimation deconstructor" << std::endl;
 //cleanUp(); 
}


GameAnimation::GameAnimation(GameMaster* theGameMaster) : SDL_Program(),mario("Mario.bmp") {
  
  std::cout << "Debug GameAnimation.cpp Line: 8 - GameAnimation Constructor start\n" << std::endl;
    
  background = loadImage("Level1Clipped.jpg");
  backRect.x = TOKEN_PANE_W;
  backRect.y = 0;
  backRect.w = GAME_WORLD_W;
  backRect.h = GAME_WORLD_H;
  scene = 0;
  gameMasterPointer = theGameMaster;
  std::cout << "GAME ANIMATION BACKGROUND RECT" << backRect.x << std::endl;

  // clip the sprite sheet
  mario.set_clips();

  // clip the background 
  clip_background();

  std::cout << "Debug GameAnimation.cpp Line: 8 - GameAnimation Constructor end\n" << std::endl;

}

// define background clip locations
void GameAnimation::clip_background() {

  
  #warning ----------------------------------------------------------
  #warning
  #warning The scene needs to move the width of the dog,
  #warning not some arbitrary amount hard coded in here.
  #warning Fix if we have more levels. It should work for now, though.
  #warning
  #warning -----------------------------------------------------------
  
  // clip the portions of the background
  for (int i = 0; i < (LEVEL_LENGTH / GAME_WORLD_W * 8); i++)
  {
    SDL_Rect tempRect;
    tempRect.x = i * (LEVEL_LENGTH / GAME_WORLD_W / 8);
    tempRect.y = 0;
    tempRect.w = GAME_WORLD_W;
    tempRect.h = GAME_WORLD_H;
    backClips.push_back(tempRect);
  }
  maxNumberOfScenes = (LEVEL_LENGTH / GAME_WORLD_W * 8);
  
}

void GameAnimation::step() {
  
  mario.status = MARIO_STEP; 
  gameMasterPointer->updateScreen();
  SDL_Delay(125);
  if (scene < maxNumberOfScenes) scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(125);
  mario.status = MARIO_STAND; 
  gameMasterPointer->updateScreen();

}

void GameAnimation::jump() {

  mario.status = MARIO_JUMP;
  mario.marioRect.y -= MARIO_HEIGHT / 2;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);
  mario.marioRect.y -= MARIO_HEIGHT / 2;
  if (scene < maxNumberOfScenes) scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);
  mario.marioRect.y += MARIO_HEIGHT / 2;
  if (scene < maxNumberOfScenes) scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);
  mario.marioRect.y += MARIO_HEIGHT / 2;
  mario.status = MARIO_STAND;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);

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

void GameAnimation::updateScreen(SDL_Surface* screen)
{
  /*                                                                         
  tempRect.x = backRect.x + background->w;                                    
  tempRect.y = backRect.y;                                                    
  tempRect.w = background->w;                                                 
  tempRect.h = background->h;                                                  
  */

  //  std::cout << "BEFORE" << backRect.x << std::endl;                        
  //  SDL_BlitSurface( background, NULL, screen, &backRect);
  // std::cout << "AFTER" << backRect.x << std::endl;                          
  //  SDL_BlitSurface( background, NULL, screen, &tempRect);                   
  SDL_BlitSurface( background, &(backClips[ scene ]), screen, &backRect);    
  mario.show(screen);
  std::cout << "SCENE IS NOW: " << scene << std::endl;
}

void GameAnimation::cleanUp()
{
  mario.cleanUp();
  SDL_FreeSurface(background);
}
