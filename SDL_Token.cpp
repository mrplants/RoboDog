//
//  SDL_Token.cpp
//  Coding Game
//
//  Created by Maribeth Rauh on 3/31/13.
//

#include "SDL_Token.h"

SDL_Token::SDL_Token(std::string ID) : SDL_Program() {
    //could put in switch statement to create token corresponding to whatever identifier was passed in
    //or we could allow the token to be customized to whatever type we need by passing in everything
    //(correct image etc.)
    
    if (!ID.compare("step"))
        tokenSurface = loadImage("tokenImages/stepToken.jpg"); //load the file for step token element
    if (!ID.compare("jump"))
        tokenSurface = loadImage("tokenImages/jumpToken.jpg"); //load the file for jump token element
    if (!ID.compare("kick"))
        tokenSurface = loadImage("tokenImages/kickToken.jpg"); //load the file for kick token element
    if (!ID.compare("turn"))
        tokenSurface = loadImage("tokenImages/turnToken.jpg"); //load the file for turn token element

    tokenRect = createRect(tokenSurface, 0, 0); //WILL NOT WORK WITH CURRENT APPLY SURFACE
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