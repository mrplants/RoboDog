#include "Mario.h"
#include "Constants.h"

Mario::Mario()
{
  //Initialize movement variables
  offSet = 0;
  x = 0;
  // y = SCREEN_HEIGHT - MARIO_HEIGHT;
  y = 480 - MARIO_HEIGHT;

  //Initialize animation variables
  status = MARIO_STAND;
}

// handle key presses
void Mario::handle_events()
{
  //If a key was pressed
  if( event.type == SDL_KEYDOWN )
    {
      //Set the status and move
      switch( event.key.keysym.sym )
        {
	case SDLK_UP: status = MARIO_JUMP; y -= 50; scrolling = 1; break;
        }
    }
    
  //If a key was released
  else if( event.type == SDL_KEYUP )
    {
      //Set the status and move
      switch( event.key.keysym.sym )
        {
	case SDLK_UP: status = MARIO_STAND; y += 50; scrolling = 0; break;
        }
    }
   
}

//Show Mario
void Mario::show()
{
  if( status == MARIO_JUMP )
    {
      apply_surface( x, y, mario, screen, &clips[ 1 ] );
    }
   if( status == MARIO_STAND )
    {
      apply_surface( x, y, mario, screen, &clips[ 0 ] );
    }
}

