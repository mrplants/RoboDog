//
//  SDL_Token.cpp
//  Coding Game
//
//  Created by Maribeth Rauh on 3/31/13.
//

#include "SDL_Token.h"

SDL_Token::SDL_Token(std::string ID) : SDL_Program()
{
    //could put in switch statement to create token corresponding to whatever identifier was passed in
    //or we could allow the token to be customized to whatever type we need by passing in everything
    //(correct image etc.)
    tokenSurface = NULL;
    
    if (!ID.compare("step"))
        tokenSurface = loadImage("tokenImages/stepToken.bmp"); //load the file for step token element
    if (!ID.compare("jump"))
        tokenSurface = loadImage("tokenImages/jumpToken.bmp"); //load the file for jump token element
    if (!ID.compare("kick"))
        tokenSurface = loadImage("tokenImages/kickToken.bmp"); //load the file for kick token element
    if (!ID.compare("turn"))
        tokenSurface = loadImage("tokenImages/turnToken.bmp"); //load the file for turn token element
	
   if (tokenSurface) tokenRect = createRect(tokenSurface, 0, 0); //WILL NOT WORK WITH CURRENT APPLY SURFACE
     
     	 number1Surface = loadImage("tokenImages/1.bmp");
	 number2Surface = loadImage("tokenImages/2.bmp");
	 number3Surface = loadImage("tokenImages/3.bmp");
	 number4Surface = loadImage("tokenImages/4.bmp");
	 number5Surface = loadImage("tokenImages/5.bmp");
}

//checks if image's associated rect is over a snap region, adjusting the offsets if it is
SDL_Rect SDL_Token::snapToLocation(SDL_Rect rect)
{
    int centerX = rect.x+(rect.w/2);
    int centerY = rect.y+(rect.h/2);
    
    /*Snap region is defined in GameMaster, needs to be passed in?
     if (centerX > snapRegion.x && centerX < snapRegion.x+snapRegion.w && centerY > snapRegion.y && centerY < snapRegion.y+snapRegion.h) {
     rect.x = snapRegion.x;
     rect.y = snapRegion.y;
     }
     */
    return rect;
}

void SDL_Token::setRect(int x, int y)
{
 tokenRect.x = x;
 tokenRect.y = y;
 return;
}

SDL_Rect SDL_Token::getRect()
{
  return tokenRect;
}

SDL_Surface * SDL_Token::getSurface()
{
  return tokenSurface;
}

void SDL_Token::cleanUp()
{
    SDL_FreeSurface(tokenSurface);
    return;
}

void SDL_Token::setSurface(SDL_Surface *newSurface)
{
  tokenSurface = newSurface;
}

SDL_Surface * SDL_Token::getNumberSurface()
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


