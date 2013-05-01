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
	std::cout << "Debug CodeToken.cpp Line: 13 - CodeToken Constructor start\n" << std::endl;
	
	_commandID = commandID;
	if (!commandID.compare("open_loop") || !commandID.compare("close_loop"))
	{
		SDL_LoopToken tempToken(commandID);
		_repeatNumber = 0;
		_uniqueLoopID = 0;
		visualToken = tempToken;
	} else
	{
		SDL_Token tempToken(commandID);
		_repeatNumber = -1;
		_uniqueLoopID = -1;
		visualToken = tempToken;
	}

	std::cout << "Debug CodeToken.cpp Line: 13 - CodeToken Constructor end\n" << std::endl;

}//the constructor, initializes with an empty identifier and position on screen

CodeToken::~CodeToken()
{
	//nothing allocated to the heap
}//the deconstructor

