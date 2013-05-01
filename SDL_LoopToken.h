/*
  SDL_LoopToken.h
  Subclassed from SDL_Token class
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013

  The visual component of a token the user puts into their code- specifically one that
  corresponds to a loop or if statement
  NOTE: This class can represent two different visual components (for and while (NOT IMPLEMENTED) loop)
 */

#ifndef SDL_LOOPTOKEN
#define SDL_LOOPTOKEN

//Base class
#include <string>
#include "SDL_Token.h" //includes all SDL frameworks, iostream, etc. needed
#include <SDL/SDL_ttf.h>


class SDL_LoopToken : public SDL_Token {
public:
	SDL_LoopToken(std::string); //parameters are ID ("if" or "loop") and subID for the action
	~SDL_LoopToken();   
    
	SDL_Surface *getNumberSurface();
        
private:
	//different surfaces depending on how many times the loop will run
	SDL_Surface * number1Surface;
	SDL_Surface * number2Surface;
	SDL_Surface * number3Surface;
	SDL_Surface * number4Surface;
	SDL_Surface * number5Surface;
	SDL_Surface * currentNumberSurface;
  
};

#endif // defined SDL_LOOPTOKEN