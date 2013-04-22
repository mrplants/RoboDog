//
//  CodeToken.h
//  Coding Game
//
//  Created by Sean Fitzgerald on 3/26/13.
//  Copyright (c) 2013 ND. All rights reserved.
//

#ifndef __Coding_Game__CodeToken__
#define __Coding_Game__CodeToken__

#include <iostream>
#include "SDL_Token.h"

class CodeToken
{
  
  public:  
	CodeToken(); //the constructor, initializes with an empty identifier and position on screen
	~CodeToken(); //the deconstructor
	
	//ViewPosition positionOnScreen; //The token's center position with respect to the view that it is in. It is public solely so that the user can invoke the special transformation methods upon it
	
	SDL_Token visualToken;
	
	std::string _commandID; //this is the token's command identifier
	int _uniqueLoopID; //this is the token's loop ID
	int _repeatNumber; //this is the number of times the loop repeats
  
};

#endif /* defined(__Coding_Game__CodeToken__) */
