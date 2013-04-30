//
//  SDL_Token.cpp
//  Coding Game
//
//  Created by Maribeth Rauh on 3/31/13.
//

#include "SDL_Token.h"

SDL_Token::SDL_Token(std::string ID) : SDL_Program() {

  std::cout << "Debug SDL_Token.cpp Line: 12 - SDL_Token Constructor start\n" << std::endl;

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

    std::cout << "Debug SDL_Token.cpp constructor - after creating a surface for the token\n" << std::endl;

	
   if (tokenSurface) tokenRect = createRect(tokenSurface, 0, 0); //WILL NOT WORK WITH CURRENT APPLY SURFACE

  std::cout << "Debug SDL_Token.cpp Line: 29 - SDL_Token Constructor end\n" << std::endl;

}

//checks if image's associated rect is over a snap region, adjusting the offsets if it is
SDL_Rect SDL_Token::snapToLocation(SDL_Rect rect) {
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

void SDL_Token::setRect(int x, int y) {
 tokenRect.x = x;
 tokenRect.y = y;
 return;
}

SDL_Rect SDL_Token::getRect() {
  return tokenRect;
}

SDL_Surface * SDL_Token::getSurface() {
  return tokenSurface;
}

void SDL_Token::cleanUp() {
    SDL_FreeSurface(tokenSurface);
    return;
}

void SDL_Token::setSurface(SDL_Surface *newSurface)
{
  tokenSurface = newSurface;
}
