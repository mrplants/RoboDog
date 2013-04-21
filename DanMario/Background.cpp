#include "Background.h"

//default constructor for Background
Background::Background()
{
  //Initialize the variables
  scrolling = 0;
  bgX = 0;
  bgY = 0;
}

// handle key presses                                                                                            
void Background::handle_events()
{
  //If a key was pressed                                                                                         
  if( event.type == SDL_KEYDOWN )
    {
      //Set the velocity                                                                                          
      switch( event.key.keysym.sym )
        {
        case SDLK_RIGHT: scrolling = 1; break;
        }
    }

  //If a key was released                                                                                         
  else if( event.type == SDL_KEYUP )
    {
      //Set the velocity                                                                                          
      switch( event.key.keysym.sym )
        {
        case SDLK_RIGHT: scrolling = 0; break;
        }
    }

}

void Background::show()
{
  //Show the Background                                                                                          
  if( scrolling == 1 )
    {
      bgX -= 50;
    }
  if( scrolling == 0 )
    {
      bgX = bgX;
    }
  //If the background has gone too far                                                                          
  if( bgX <= -background->w )
    {
      //Reset the offset                                                                                        
      bgX = 0;
    }

  //Show the background                                                                                         
  apply_surface( bgX, bgY, background, screen );
  apply_surface( bgX + background->w, bgY, background, screen );
}
