/*
  CodeToken.cpp
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  Data side of the tokens that the user drags out of a library to run their program
  
  Composed classes:
    SDL_Token - the visual component of each token
    NOTE: this could also be an SDL_LoopToken, a derived class of SDL_Token
  */

#include "CodeToken.h"

//the constructor, initializes with an empty identifier and position on screen
CodeToken::CodeToken(std::string commandID)
{	
	_commandID = commandID;
	if (!commandID.compare("open_loop") || !commandID.compare("close_loop")) {
		SDL_LoopToken tempToken(commandID);
		_repeatNumber = 0;
		_uniqueLoopID = 0;
		visualToken = tempToken;
	}else{
		SDL_Token tempToken(commandID);
		_repeatNumber = -1;
		_uniqueLoopID = -1;
		visualToken = tempToken;
	}
}

//the deconstructor
CodeToken::~CodeToken()
{
	//nothing allocated to the heap
}

