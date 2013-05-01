/*
  SDL_LoopToken.cpp
  Subclassed from SDL_Token class
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013

  The visual component of a token the user puts into their code- specifically one that
  corresponds to a loop or if statement
  NOTE: This class can represent two different visual components (for and while (NOT IMPLEMENTED) loop)
 */

#include "SDL_LoopToken.h"

SDL_LoopToken::~SDL_LoopToken() {}

//constructor
SDL_LoopToken::SDL_LoopToken(std::string ID) : SDL_Token(ID) 
{
	if (!ID.compare("open_loop"))
		 setSurface(loadImage("tokenImages/openLoopToken.bmp")); //load the file for open_loop token element
		 
	if (!ID.compare("close_loop"))
		setSurface(loadImage("tokenImages/closeLoopToken.bmp")); //load the file for close_loop token element

	tokenRect = createRect(getSurface(), 0, 0);
	
	SDL_Surface * number1Surface = loadImage("tokenImages/1.bmp");
	SDL_Surface * number2Surface = loadImage("tokenImages/2.bmp");
	SDL_Surface * number3Surface = loadImage("tokenImages/3.bmp");
	SDL_Surface * number4Surface = loadImage("tokenImages/4.bmp");
	SDL_Surface * number5Surface = loadImage("tokenImages/5.bmp");
}

SDL_Surface * SDL_LoopToken::getNumberSurface()
{
	switch (_repeatNumber) {
		case (1):
			currentNumberSurface = number1Surface;
			break;
		case (2):
			currentNumberSurface = number2Surface;
			break;
		case (3):
			currentNumberSurface = number3Surface;
			break;
		case (4):
			currentNumberSurface = number4Surface;
			break;
		case (5):
			currentNumberSurface = number5Surface;
			break;
		default :
			currentNumberSurface = number1Surface;
			break;
	}
	return currentNumberSurface;
}

