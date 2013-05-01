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

  congratulatory = loadImage("WinnerScreen.jpg");

  loser = loadImage("LoserScreen.jpg");

  enemy = loadImage("enemy.bmp");
  enemyRect.x = SCREEN_WIDTH - TOKEN_LIB_W + MARIO_WIDTH;
  enemyRect.y = SCREEN_HEIGHT - TOKEN_LIB_H - RUN_BUTTON_H - ENEMY_HEIGHT;
  enemyRect.w = ENEMY_WIDTH;
  enemyRect.h = ENEMY_HEIGHT;

  killedEnemy = 0;

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
    backClips[ i ].x = i * (LEVEL_LENGTH / (LEVEL_LENGTH / GAME_WORLD_W * 24));
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

// checks if Mario has killed the enemy
void GameAnimation::didKill() {
  
  // if Mario is at scene 100 and kicks the enemy, increment the killedEnemy counter
  if (scene == 100 && mario.status == MARIO_KICK) {
    killedEnemy++;
  }
  
}

void GameAnimation::updateScreen(SDL_Surface* screen)
{

  // if Mario has hit the first wall, show a loser screen
  if (scene == 20 && mario.status == MARIO_STAND) {
    SDL_BlitSurface( loser, NULL, screen, &backRect);
  }
  // if Mario has hit the second wall, show a loser screen
  else if (scene == 52 && mario.status == MARIO_STAND) {
    SDL_BlitSurface( loser, NULL, screen, &backRect);
  }
  // if Mario has not killed the enemy, show a loser screen 
  else if ( scene >= 104 && killedEnemy < 1) {
    SDL_BlitSurface( loser, NULL, screen, &backRect);
  }
  // if Mario has reached the end of the level, show a winner screen
  else if (scene >= 116 ) {
    SDL_BlitSurface( congratulatory, NULL, screen, &backRect);  
  }  
  // otherwise, show Mario and the appropriate scene of the background
  else {
    SDL_BlitSurface( background, &backClips[ scene ], screen, &backRect);    
    if (scene >= 100) {
      // check if Mario has killed the enemy
      didKill();
      // if Mario has not kicked the enemy at least once, display the enemy
      if (killedEnemy < 1) {
	SDL_BlitSurface( enemy, NULL, screen, &enemyRect ); 
      }
    }
    mario.show(screen);
  }

  std::cout << "SCENE IS NOW: " << scene << std::endl;
  std::cout << "MARIO'S STATUS IS: " << mario.status << std::endl;
  std::cout << "KILLED ENEMY IS EQUAL TO: " << killedEnemy << std::endl;
}

void GameAnimation::cleanUp()
{

  mario.cleanUp();
  SDL_FreeSurface(background);

}
