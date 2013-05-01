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

SDL_LoopToken::~SDL_LoopToken()
{
	//Close a font that was used
}

SDL_LoopToken::SDL_LoopToken(std::string ID) : SDL_Token(ID) 
{
	std::cout << "Debug SDL_LoopToken.cpp Line: 15 - SDL_LoopToken Constructor start\n" << std::endl;

	if (!ID.compare("open_loop"))
		 setSurface(loadImage("tokenImages/openLoopToken.bmp")); //load the file for open_loop token element
		 
	if (!ID.compare("close_loop"))
		setSurface(loadImage("tokenImages/closeLoopToken.bmp")); //load the file for close_loop token element

	tokenRect = createRect(getSurface(), 0, 0); //WILL NOT WORK WITH CURRENT APPLY SURFACE
	
	SDL_Surface * number1Surface = loadImage("tokenImages/1.bmp");
	SDL_Surface * number2Surface = loadImage("tokenImages/2.bmp");
	SDL_Surface * number3Surface = loadImage("tokenImages/3.bmp");
	SDL_Surface * number4Surface = loadImage("tokenImages/4.bmp");
	SDL_Surface * number5Surface = loadImage("tokenImages/5.bmp");

    /*
	//set up the fontColor
	fontColor = { 255, 255, 0 };
	theFont = TTF_OpenFont( "repeatNumberFont.TTF", 50 ); 	
	tokenRepeatMessage = "1";
	
	//load text surface
	if (!(messageSurface = TTF_RenderText_Solid(theFont, tokenRepeatMessage.c_str(), fontColor)))
		std::cout << "ERR: " << TTF_GetError() << std::endl;
    
        std::cout << "Debug SDL_LoopToken.cpp Line: 15 - render text\n" << std::endl;
        std::cout << "Debug SDL_LoopToken.cpp Line: 15 - messageSurface:" << messageSurface << std::endl;

	messageSurfaceRect.w = messageSurface->w;
	std::cout << "Debug SDL_LoopToken.cpp Line: 15 - set width\n" << std::endl;

	messageSurfaceRect.h = messageSurface->h;
	std::cout << "Debug SDL_LoopToken.cpp Line: 1d5 - set height\n" << std::endl;

	messageSurfaceRect.x = tokenRect.x + tokenRect.w / 2 - messageSurface->w / 2;
	std::cout << "Debug SDL_LoopToken.cpp Line: 15 - set X coordinate\n" << std::endl;

	messageSurfaceRect.y = tokenRect.y + tokenRect.h / 2 - messageSurface->h / 2;
    
	std::cout << "Debug SDL_LoopToken.cpp Line: 15 - SDL_LoopToken Constructor end\n" << std::endl;*/
}

SDL_Surface * SDL_LoopToken::getNumberSurface()
{
  std::cout << "Debug SDL_LoopToken getMessageSurface() : entered getMessage Surface function." << std::endl;
  switch (_repeatNumber)
  {
    case (1):
      currentNumberSurface = number1Surface;
  std::cout << "Debug SDL_LoopToken getMessageSurface() : number is 1." << std::endl;
      break;
    case (2):
      currentNumberSurface = number2Surface;
  std::cout << "Debug SDL_LoopToken getMessageSurface() : number is 2." << std::endl;
      break;
    case (3):
      currentNumberSurface = number3Surface;
  std::cout << "Debug SDL_LoopToken getMessageSurface() : number is 3." << std::endl;
      break;
    case (4):
      currentNumberSurface = number4Surface;
  std::cout << "Debug SDL_LoopToken getMessageSurface() : number is 4." << std::endl;
      break;
    case (5):
      currentNumberSurface = number5Surface;
  std::cout << "Debug SDL_LoopToken getMessageSurface() : number is 5." << std::endl;
      break;
    default :
      currentNumberSurface = number1Surface;
      break;
  }
  /*
  messageSurface = TTF_RenderText_Solid(theFont, tokenRepeatMessage.c_str(), fontColor);
  messageSurfaceRect.w = getRect().w;
  messageSurfaceRect.h = getRect().h;
  messageSurfaceRect.x = getRect().x + getRect().w / 2 - messageSurface->w / 2;
  messageSurfaceRect.y = getRect().y + getRect().h / 2 - messageSurface->h / 2;
  std::cout << "SDL_LoopToken getMessageSurface: " << messageSurfaceRect.x << ", " << messageSurfaceRect.y << std::endl;

  std::cout << "Debug SDL_LoopToken getMessageSurface() : leaving getMessage Surface function." << std::endl;

  */
  return currentNumberSurface;
}

