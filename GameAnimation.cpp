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
  //congratulatory = loadImage("winner.jpg");
  //loser = loadImage("loser.jpg");
  gameMasterPointer = theGameMaster;
  
  // clip the sprite sheet
  mario.set_clips();
  
  // clip the background 
  clip_background();

  std::cout << "Debug GameAnimation.cpp Line: 8 - GameAnimation Constructor end\n" << std::endl;

}

// define background clip locations
void GameAnimation::clip_background() {

  // clip the portions of the background
  for (int i = 0; i < (LEVEL_LENGTH / GAME_WORLD_W * 24); i++)
  {
    std::cout << "AMOUNT OF CLIPS: " << (LEVEL_LENGTH / GAME_WORLD_W * 24) << std::endl;
    backClips[ i ].x = i * (LEVEL_LENGTH / (LEVEL_LENGTH / GAME_WORLD_W * 24));
    std::cout<<"X IS: " << backClips[ i ].x << std::endl;
    backClips[ i ].y = 0;
    backClips[ i ].w = GAME_WORLD_W;
    backClips[ i ].h = GAME_WORLD_H;
  }
  
}

void GameAnimation::step() {
  mario.status = MARIO_STEP; 
  gameMasterPointer->updateScreen();
  SDL_Delay(125);
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(125);
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(125);
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(125);
  scene++;
  mario.status = MARIO_STAND;
  gameMasterPointer->updateScreen();
 
}

void GameAnimation::jump() {

  mario.status = MARIO_JUMP;

  mario.marioRect.y -= MARIO_HEIGHT / 8;
  gameMasterPointer->updateScreen();
  SDL_Delay(5);
  mario.marioRect.y -= MARIO_HEIGHT / 8;
  gameMasterPointer->updateScreen();
  SDL_Delay(10);
  mario.marioRect.y -= MARIO_HEIGHT / 8;
  gameMasterPointer->updateScreen();
  SDL_Delay(15);
  mario.marioRect.y -= MARIO_HEIGHT / 8;
  gameMasterPointer->updateScreen();
  SDL_Delay(20);

  mario.marioRect.y -= MARIO_HEIGHT / 8;
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(30);
  mario.marioRect.y -= MARIO_HEIGHT / 8;
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(50);
  mario.marioRect.y -= MARIO_HEIGHT / 8;
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(55);
  mario.marioRect.y -= MARIO_HEIGHT / 8;
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(65);

  mario.marioRect.y += MARIO_HEIGHT / 8;
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(65);
  mario.marioRect.y += MARIO_HEIGHT / 8;
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(55);
  mario.marioRect.y += MARIO_HEIGHT / 8;
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(50);
  mario.marioRect.y += MARIO_HEIGHT / 8;
  scene++;
  gameMasterPointer->updateScreen();
  SDL_Delay(30);

  mario.marioRect.y += MARIO_HEIGHT / 8;
  gameMasterPointer->updateScreen();
  SDL_Delay(20);
  mario.marioRect.y += MARIO_HEIGHT / 8;
  gameMasterPointer->updateScreen();
  SDL_Delay(15);
  mario.marioRect.y += MARIO_HEIGHT / 8;
  gameMasterPointer->updateScreen();
  SDL_Delay(10);
  mario.marioRect.y += MARIO_HEIGHT / 8;
  mario.status = MARIO_STAND;
  gameMasterPointer->updateScreen();
  SDL_Delay(5);

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
  /*
  if (scene == 20 && mario.marioRect.x == 176) {
    SDL_BlitSurface( loser, NULL, screen, &backRect);
  }
  else if (scene == 52 && mario.marioRect.x == 176) {
    SDL_BlitSurface( loser, NULL, screen, &backRect);
  }
  else if (scene >= 116 ) {
    SDL_BlitSurface( congratulatory, NULL, screen, &backRect);  
  }  
  else {
  */
    SDL_BlitSurface( background, &backClips[ scene ], screen, &backRect);    
    mario.show(screen);
    // }
  std::cout << "SCENE IS NOW: " << scene << std::endl;
  std::cout << "MARIO'S X IS: " << mario.marioRect.x << std::endl;
  std::cout << "MARIO'S STATUS IS: " << mario.status << std::endl;
}

void GameAnimation::cleanUp()
{
  mario.cleanUp();
  SDL_FreeSurface(background);
}
