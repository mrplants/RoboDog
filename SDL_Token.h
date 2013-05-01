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

//Base class
#include "SDL_Program.h" //includes all SDL frameworks, iostream, etc. needed

class SDL_Token : public SDL_Program {
public:
    SDL_Token(std::string = "default.bmp");
    
    SDL_Rect snapToLocation(SDL_Rect); //checks if image's associated rect is over a snap region, adjusting the offsets if it is
    
    void setPosition(int, int); //parameters are absolute coordinates
    void translate(int, int); //parameters are change in position relative to its previous position
    
    void setRect(int, int);
    SDL_Rect getRect();
    SDL_Surface *getSurface();
    void setSurface(SDL_Surface*);
    
    virtual void cleanUp();
    
    SDL_Rect tokenRect;
    SDL_Surface *tokenSurface;
    SDL_Surface *getNumberSurface();
    
    
    int _repeatNumber;

    
private:
  SDL_Surface * number1Surface;
  SDL_Surface * number2Surface;
  SDL_Surface * number3Surface;
  SDL_Surface * number4Surface;
  SDL_Surface * number5Surface;
  SDL_Surface * currentNumberSurface;
};

#endif /* defined SDL_TOKEN */
