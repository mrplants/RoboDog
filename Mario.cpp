#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// default constructor
Mario::Mario()
{
  //Initialize movement variables
  marioRect.x = 0;
  marioRect.y = SCREEN_HEIGHT - MARIO_HEIGHT;

  //Initialize animation variables
  status = MARIO_STAND;

  //Create the Mario surface
  marioSurface = load_image( "Mario.bmp" );
}

// figure out how to pass in screen
void Mario::show(SDL_Surface *screen)
{
  //Show Mario
  if( status == MARIO_STAND )
    {
      SDL_BlitSurface( marioSurface, &clipsStand[ frame ], screen, &marioRect); 
    }

  if( status == MARIO_STEP ) 
    {
      SDL_BlitSurface( marioSurface, &clipsStep[ frame ], screen, &marioRect);
      frame++;
    }

  if( status == MARIO_


  // include all other statuses

}

// define clip locations                                                                                                                                        
void set_clips()
{
  //Clip the sprites                                                                                                                                         
  clips[ 0 ].x = 0;
  clips[ 0 ].y = 0;
  clips[ 0 ].w = MARIO_WIDTH;
  clips[ 0 ].h = MARIO_HEIGHT;

  clips[ 1 ].x = MARIO_WIDTH;
  clips[ 1 ].y = 0;
  clips[ 1 ].w = MARIO_WIDTH;
  clips[ 1 ].h = MARIO_HEIGHT;
}


// clean up function for Mario
void Mario::cleanUp() {

  SDL_FreeSurface( marioSurface );

}
