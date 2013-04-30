#include "GameAnimation.h"
#include "GameMaster.h"

GameAnimation::GameAnimation() : SDL_Program() {}

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

  // clip the portions of the background
  for (i = 0; i < LEVEL_LENGTH / GAME_WORLD_W * 8 - 1; i++) { 
    backClip[ i ].x = i * LEVEL_LENGTH / GAME_WORLD_W / 8;
    backClip[ i ].y = 0;
    backClip[ i ].w = GAME_WORLD_W;
    backClip[ i ].h = GAME_WORLD_H;
  }
  
}

void GameAnimation::step() {
  
  mario.status = MARIO_STEP; 
  gameMasterPointer->updateScreen();
  gameMasterPointer->updateScreen();
  SDL_Delay(125);
  scene++;
  gameMasterPointer->updateScreen();
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
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(250);
  mario.marioRect.y += MARIO_HEIGHT / 2;
  scene++;
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
  SDL_BlitSurface( background, &backClips[ scene ], screen, &backRect);    
  mario.show(screen);

}

void GameAnimation::cleanUp()
{
  mario.cleanUp();
  SDL_FreeSurface(background);
}
