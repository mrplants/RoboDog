/*
  CodeToken.h
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  Data side of the tokens that the user drags out of a library to run their program
  
  Composed classes:
    SDL_Token - the visual component of each token
    NOTE: this could also be an SDL_LoopToken, a derived class of SDL_Token
  */

#ifndef __Coding_Game__CodeToken__
#define __Coding_Game__CodeToken__

#include <iostream>
#include "SDL_LoopToken.h"
#include "SDL_Token.h"

class CodeToken
{
  public:  
	CodeToken(std::string); //the constructor, initializes with an empty identifier and position on screen
	~CodeToken(); //the deconstructor

	SDL_Token visualToken;
	
	std::string _commandID; //this is the token's command identifier
	int _uniqueLoopID; //this is the token's loop ID (-1 if not a loop)
	int _repeatNumber; //this is the number of times the loop repeats (-1 if not a loop)
  
};

#endif /* defined(__Coding_Game__CodeToken__) */
