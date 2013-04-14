//
//  SDL_Token.h
//  Coding Game
//
//  Created by Maribeth Rauh on 3/31/13.s
//
//     This class, derived from the SDL_Program base class, is the visual component of the tokens the
//  user is clicking and dragging to put together their code to be placed in a queue and run through the
//  interpreter.
//  NOTE: Some tokens will be instances of this class, others will be instances of more specific derived classes

#ifndef SDL_TOKEN
#define SDL_TOKEN

#include <iostream>
#include <string>
#include "SDL_Program.h" //includes all SDL frameworks needed

class SDL_Token : public SDL_Program {
public:
    SDL_Token(std::string);
    
    SDL_Rect snapToLocation(SDL_Rect); //checks if image's associated rect is over a snap region, adjusting the offsets if it is
    
    void setPosition(int, int); //parameters are absolute coordinates
    void translate(int, int); //parameters are change in position relative to its previous position
    SDL_Rect getRect();
    
    virtual void cleanUp();
    
private:
    SDL_Surface *token;
    SDL_Rect tokenRect;
    
};

#endif /* defined SDL_TOKEN */
