//
//  CodeToken.cpp
//  Coding Game
//
//  Created by Sean Fitzgerald on 3/26/13.
//  Copyright (c) 2013 ND. All rights reserved.
//

#include "CodeToken.h"

CodeToken::CodeToken(std::string commandID)
{
	_commandID = commandID;
	if (!commandID.compare("open_loop"))
	{
		visualToken = SDL_LoopToken();
		_repeatNumber = 0;
		_uniqueLoopID = 0;
	} else
	{
		visualToken = SDL_Token();
		_repeatNumber = -1;
		_uniqueLoopID = -1;
	}
}//the constructor, initializes with an empty identifier and position on screen

CodeToken::~CodeToken()
{
	//nothing allocated to the heap
}//the deconstructor
