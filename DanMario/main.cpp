#include "Defines.h"
#include "Mario.h"
#include "Background.h"

//main function
int main( int argc, char* args[] )
{
  //Quit flag
  bool quit = false;

  //Initialize
  if( init() == false )
    {
      return 1;
    }

  //Load the files
  if( load_files() == false )
    {
      return 1;
    }

  //Clip the sprite sheet                                                    
  set_clips();

  //instantiate Mario                                                         
  Mario character;

  //instantiate Background
  Background back;

  //While the user hasn't quit
  while( quit == false )
    {
      //While there's events to handle
      while( SDL_PollEvent( &event ) )
        {
	  //If the user has Xed out the window
	  if( event.type == SDL_QUIT )
            {
	      //Quit the program
	      quit = true;
            }
        }
      
      back.show();
      character.show();

      //Update the screen
      if( SDL_Flip( screen ) == -1 ) {
	return 1;
      }
      
  //Clean up
  clean_up();
  
  return 0;
}
