/*
 * SDL_LoopToken.cpp
 *
 * Created by Maribeth E Rauh
 *
 * The visual component of a token the user puts into their code- specifically one that
 * corresponds to a loop or if statement
 * NOTE: This class will represent two different visual components (for and while loop)
 */

#include "SDL_LoopToken.h"

SDL_LoopToken::SDL_LoopToken(std::string ID) : SDL_Token(ID) 
{
	std::cout << "Debug SDL_LoopToken.cpp Line: 15 - SDL_LoopToken Constructor start\n" << std::endl;

	if (!ID.compare("open_loop"))
		 setSurface(loadImage("tokenImages/openLoopToken.bmp")); //load the file for open_loop token element
		 
	if (!ID.compare("close_loop"))
		setSurface(loadImage("tokenImages/closeLoopToken.bmp")); //load the file for close_loop token element

    tokenRect = createRect(getSurface(), 0, 0); //WILL NOT WORK WITH CURRENT APPLY SURFACE
    
    
    //set up the fontColor
    fontColor = { 255, 255, 0 };
    theFont = TTF_OpenFont( "repeatNumberFont.ttf", 28 ); 	
	std::cout << "Debug SDL_LoopToken.cpp Line: 15 - SDL_LoopToken Constructor end\n" << std::endl;

}

SDL_Surface * SDL_LoopToken::getMessageSurface()
{
  switch (_repeatNumber) {
    case (0) :
      tokenRepeatMessage = "0";
      break;
    case (1):
      tokenRepeatMessage = "1";
      break;
    case (2):
      tokenRepeatMessage = "2";
      break;
    case (3):
      tokenRepeatMessage = "3";
      break;
    case (4):
      tokenRepeatMessage = "4";
      break;
    case (5):
      tokenRepeatMessage = "5";
      break;
    default :
      tokenRepeatMessage = " ";
      break;
  }
  
  messageSurface = TTF_RenderText_Solid(theFont, tokenRepeatMessage.c_str(), fontColor);
  messageSurfaceRect.w = messageSurface->w;
  messageSurfaceRect.h = messageSurface->h;
  messageSurfaceRect.x = getRect().w / 2 - messageSurface->w / 2;
  messageSurfaceRect.y = getRect().h / 2 - messageSurface->h / 2;

  return messageSurface;
}
