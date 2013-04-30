//
//  TokenQueue.cpp
//  Coding Game
//
//  Created by Sean Fitzgerald on 3/26/13.
//  Copyright (c) 2013 ND. All rights reserved.
//

#include "TokenQueue.h"

#pragma mark -
#pragma mark private
/*
void TokenQueue::dispatchTokensToInterpreterInThread(std::deque<CodeToken>, pthread_t)
{
	//check if there's a thread already. If there isn't, then create one and dispatch the tokenDeque to it with an interpreter function call. If there is, then do nothing. There shouldn't be two interpreter programs running concutively. If we think there should, then we can implement that here later
}

void *TokenQueue::runTokenInInterpretter(threadTokenDataStruct)
//THIS MUST ONLY BE CALLED FROM A SEPARATE THREAD!!!!!!
{
	//threading data...
	return NULL;
}
*/
#pragma mark -
#pragma Destructor and Constructor

TokenQueue::TokenQueue()
{

  std::cout << "Debug TokenQueue.cpp Line: 32 - TokenQueue Constructor start\n" << std::endl;

	activeTokenPtr = NULL;

  std::cout << "Debug TokenQueue.cpp Line: 37 - TokenQueue Constructor end\n" << std::endl;

}
//constructor

TokenQueue::~TokenQueue()
{
	
	pthread_exit(NULL);
	
}
//destructor. Deletes all tokens from memory

#pragma mark -
#pragma mark Methods About Dispatching Code

/*
void TokenQueue::dispatchTokenQueueToInterpreter()
{
	//I need to work with John and the interpreter team
}
//this calls the tokenQueue to start dispatching
//NB: IF THE PROGRAM WAS DISPATCHED AND PAUSED, IT WILL NOT GO TO THE BEGINNING UNLESS REWOUND. IT WILL CONTINUE FROM THE LAST TOKEN DISPATCHED.

void TokenQueue::pauseDispatching()
{
	//I need to work with John and the interpreter code
}
//temporarily pauses the dispatching of the program to the interpreter
void TokenQueue::rewind()
{
	_interpreterProcessingIndex = 0;
}
//rewind the tokenQueue so that the next call of dispatchQueueToInterpreter() will start dispatching from the first token

void TokenQueue::unDispatchTokenQueueFromInterpreter()
{
	//I need to work with John and the interpreter code
}
//starts pulling tokens back through the interpreter to undo what they have done. Maybe an extra feature. Very cool to have...

void TokenQueue::setWaitTime(int waitTime)
{
	_waitTime = waitTime;
}
//sets the time between token dispatches to the interpretter

int TokenQueue::getWaitTime()
{
	return _waitTime;
}
//gets the time between token dispatches to the interpretter
*/
#pragma mark -
#pragma mark Methods About Changing the Queue

void TokenQueue::addTokenToEnd(CodeToken newToken)
{
	if (!newToken._commandID.compare("close_loop")) {
		CodeToken newLoopToken("open_loop");
		newLoopToken._repeatNumber = newToken._repeatNumber;
		newLoopToken._uniqueLoopID = newToken._uniqueLoopID;
		_tokenDeque.push_back(newLoopToken);
	}
	else {
	  _tokenDeque.push_back(newToken);
	}
}
//adds a token to the end of the tokenQueue
 
void TokenQueue::removeTokenAtIndex(int index)
{
  if (!_tokenDeque[index]._commandID.compare("open_loop") || !_tokenDeque[index]._commandID.compare("close_loop"))
  {
    //save the loop ID number so that you can take out all the blocks with that ID number
    int uniqueLoopID = _tokenDeque[index]._uniqueLoopID;

    //delete the two (start and end) loop tokens with that ID number
    for (int i = 0; i < _tokenDeque.size(); ++i)
    {
      if (_tokenDeque[i]._uniqueLoopID == uniqueLoopID)
      {
         _tokenDeque.erase(_tokenDeque.begin() + i);
	 i = 0;
      }
    }


  }
  else _tokenDeque.erase(_tokenDeque.begin() + index);
}
//removes the token at the specified index and deletes it from memory if the token is a loop, it deletes both loop tokens

bool TokenQueue::mouseOverToken(int x, int y)
{
	std::cout << "in mouseOverToken" << std::endl;
	//iterate through all existing tokens to see if the mouse was clicked on one
	//make that token active if so
	for (int i=0; i < _tokenDeque.size(); i++) {
	  std::cout << "Debug TokenDeque mouseOverToken: checking if over token at index: " << i << std::endl;
		if (_tokenDeque[i].visualToken.mouseOverImage(_tokenDeque[i].visualToken.getRect(), x, y))
		{
		    shiftTokensUp(i+1);
		    //addTokenToEnd(_tokenDeque[i]);
		    //activeToken = &(_tokenDeque.back());
		    activeTokenPtr = new CodeToken(_tokenDeque[i]);
		    //activeToken = _tokenDeque[i];
		    //activeTokenPtr = &activeToken;
		    removeTokenAtIndex(i);
		    std::cout << "Token made active in mouseOverToken" << std::endl;
		    return true;
		}
	}
  
	//if none was made active, check if the mouse clicked in the library
	//potentially make a new token if so
	if (overTokenStack(x, y, 0)) {
	  //instantiate loop token
	  std::cout << "step token!" << std::endl;
	  newToken("step",  TOKEN_LIB_START_X+(0)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	}else if (overTokenStack(x, y, 1)) {
	  //instantiate step token
	  std::cout << "turn token!" << std::endl;
	  newToken("turn",  TOKEN_LIB_START_X+(1)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	}else if (overTokenStack(x, y, 2)) {
	  //instantiate jump token
	  std::cout << "kick token!" << std::endl;
	  newToken("kick",  TOKEN_LIB_START_X+(2)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	}else if (overTokenStack(x, y, 3)) {
	  //instantiate kick token
	  std::cout << "jump token!" << std::endl;
	  newToken("jump",  TOKEN_LIB_START_X+(3)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	}else if (overTokenStack(x, y, 4)) {
	  //instantiate turn token
	  std::cout << "loop token!" << std::endl;
	  newToken("open_loop", TOKEN_LIB_START_X+(4)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	}
	std::cout << "not over library or pane" << std::endl;
  return false;
}
//checks if the mouse was clicked over an existing token or one in the library

bool TokenQueue::overTokenStack(int x, int y, int i) 
{
	if (x > TOKEN_LIB_START_X+i*TOKEN_STACK_W && x < TOKEN_LIB_START_X+(i+1)*TOKEN_STACK_W) {
	  if (y > SCREEN_HEIGHT-TOKEN_LIB_H && y < SCREEN_HEIGHT) {
	    return true;
	  }
	}
	return false; 
}

void TokenQueue::newToken(std::string commandID, int x, int y)
{
	std::cout << "Debug TokenQueue.cpp newToken: before instatiating a new Token\n" << std::endl;

	CodeToken newToken(commandID);
	    std::cout << "Debug TokenQueue.cpp newToken: after instantiating a new token\n" << std::endl;

	newToken.visualToken.setRect(x, y);
	newToken._commandID = commandID;

	if(commandID.compare("open_loop")) {
		// This token is not a loop so we set their repeat number and loop ID to -1
		newToken._repeatNumber = -1;
		newToken._uniqueLoopID = -1;
	
	}else { //this token IS a loop token
		std::cout << "Debug TokenQueue.cpp newToken: This is a loop token\n" << std::endl;
		newToken._repeatNumber = 1;

		//get a unique loop ID by parsing all the other loop tokens
		int uniqueLoopID = 0;
		for (int i = 0; i < _tokenDeque.size(); i++) {
		  
			if (!_tokenDeque[i]._commandID.compare("open_loop"))
			  uniqueLoopID++; //oops, this unique ID is taken by some other loop;
		}
		
		newToken._uniqueLoopID = uniqueLoopID;
		
		std::cout << "Debug TokenQueue.cpp newToken: new LOOP TOKEN with ID number: " << uniqueLoopID << std::endl;

	}

  #warning Only the open_loop token is pushed with creation.
  #warning When the mouse is released and open_loop is added to the deque, close_loop is added below it.
  #warning To do this, we must also have remove functions such that if you click on either an "open" or a "close", and pull it out, both are removed.


	//_tokenDeque.push_back(newToken); //put the token at the back of the deque in the activeToken spot
	//activeToken = &(_tokenDeque.back());
	//activeToken = newToken;
	activeTokenPtr = new CodeToken(newToken);
	return;
}

#pragma mark -
#pragma mark Methods About Accessing the Queue

std::vector<std::vector<int> > TokenQueue::getInterpreterVector()
{
  // the vector with the interpreters commands
  std::vector<std::vector<int> > returnVector;

  // loops throught he tokens and adds their identifiers to the vector
  for(int i = 0; i < _tokenDeque.size(); i++)
  {
    std::vector<int> tokenVectorOfIdentifiers;

//------------These are the token identifiers. If you use other identifiers, it wont work.-------------- 
#warning Maybe we should #define these token identifiers somewhere?

//1 - "step"
//2 - "jump"
//3 - "turn"
//4 - "kick"
//5 - "open_loop"
//6 - "close_loop"
//------------------------------------------------------------------------------------------------------

    //store the command ID of the token
    if (!_tokenDeque[i]._commandID.compare("step"))
      tokenVectorOfIdentifiers.push_back(1);
    else if (!_tokenDeque[i]._commandID.compare("jump"))
      tokenVectorOfIdentifiers.push_back(2);
    else if (!_tokenDeque[i]._commandID.compare("turn"))
      tokenVectorOfIdentifiers.push_back(3);
    else if (!_tokenDeque[i]._commandID.compare("kick"))
      tokenVectorOfIdentifiers.push_back(4);
    else if (!_tokenDeque[i]._commandID.compare("open_loop"))
      tokenVectorOfIdentifiers.push_back(5);
    else if (!_tokenDeque[i]._commandID.compare("close_loop"))
      tokenVectorOfIdentifiers.push_back(6);

    //store the loop identifier
    tokenVectorOfIdentifiers.push_back(_tokenDeque[i]._repeatNumber);

    //store the number of repeats in the loop
    tokenVectorOfIdentifiers.push_back(_tokenDeque[i]._uniqueLoopID);

    //store the tokens identifiers to the vector<vector<int> >
    returnVector.push_back(tokenVectorOfIdentifiers);
    
    std::cout << "Debug TokenDeque.cpp, getInterpreterVector - token number: " << i << "has commandID: " << returnVector[i][0] << std::endl;
    
  }
  return returnVector;
}

CodeToken TokenQueue::getTokenAtIndex(int index)
{
	return _tokenDeque.at(index);
}
//returns a reference to the token at the specified index

CodeToken TokenQueue::operator[](int index)
{
	return _tokenDeque.at(index);
}

const CodeToken TokenQueue::TokenQueue::operator[](int index) const
{
	return _tokenDeque.at(index);
}

void TokenQueue::printQueue()
{
	for (int i=0; i < _tokenDeque.size(); i++) {
		std::cout << i << " " << _tokenDeque[i]._commandID << ": " << _tokenDeque[i].visualToken.getRect().x << ", " << _tokenDeque[i].visualToken.getRect().y << std::endl;
	}
	return; 
}

#pragma mark -
#pragma mark Methods About Manipulating Tokens on the Screen

void TokenQueue::translateActiveToken(int dx, int dy)
{
  if (activeTokenPtr)
	translateToken(activeTokenPtr, dx, dy);
}

void TokenQueue::snapActiveToken()
{
	//finds the index of the new active token
	std::deque<CodeToken>::iterator it = _tokenDeque.begin();
	SDL_Rect activeTokenRect = (*activeTokenPtr).visualToken.getRect();
  
	int i;
	for (i = 0; it != _tokenDeque.end(); it++) {
		std::cout << "Debug snapActiveToken Line 326: current i = " << i << std::endl;
		SDL_Rect currentTokenRect = _tokenDeque[i].visualToken.getRect();
		//when the token that was dropped is above the next token, its spot in the queue has been found
		if (currentTokenRect.y > activeTokenRect.y) {
			std::cout << "Debug snapActiveToken Line 317: active token goes above " << currentTokenRect.y << std::endl;
			break;
		}
		i++;
	}
	std::cout << "Debug snapActionToken Line 335: i AFTER LOOP = " << i << std::endl;
	i;
	_tokenDeque.insert(it, *activeTokenPtr);
	
	//places the newly dropped token on the screen
	//Note: all tokens have the same x coordinate
	std::cout << "Debug snapActiveToken Line 328: token placed at " << TOKENS_X << ", " << TOKENS_START_Y + i*(TOKEN_H/*EIGHT*/+TOKEN_SPACING) << std::endl;
	_tokenDeque[i].visualToken.setRect(TOKENS_X, TOKENS_START_Y + i*(TOKEN_H/*EIGHT*/+TOKEN_SPACING));
	SDL_Rect tempRect = _tokenDeque[i].visualToken.getRect();
	std::cout << "Debug snapActiveToken Line 330: token placed at " << tempRect.x << ", " << tempRect.y << std::endl;


	//if the token is a loop token, then we need to add a close loop underneath it
	if (!(*activeTokenPtr)._commandID.compare("open_loop")) {
	  
	  	std::cout << "Debug snapActiveToken Line 330: HOLY SHIT A LOOP TOKEN GETTING PLACED? ARE YOU CRAZY? " << tempRect.x << ", " << tempRect.y << std::endl;
	  	std::cout << "Debug snapActiveToken Line 330: close token inserted before index: " << i+1 << std::endl;

		CodeToken closeLoopToken("close_loop");
		closeLoopToken._uniqueLoopID = (*activeTokenPtr)._uniqueLoopID;
		closeLoopToken._repeatNumber = (*activeTokenPtr)._repeatNumber;
		closeLoopToken.visualToken.setRect(TOKENS_X, TOKENS_START_Y + (i+1)*(TOKEN_H/*EIGHT*/+TOKEN_SPACING));
		
		//add the close loop token to the deque directly after the open loop
		if (it == _tokenDeque.end()) {
			_tokenDeque.push_back(closeLoopToken);
		}else{
			it++;
			_tokenDeque.insert(it, closeLoopToken);
		}
			
		//update close loop's rect as well
		//i++;
		std::cout << "Debug snapActiveToken Line 341: close loop placed at " << TOKENS_X << ", " << TOKENS_START_Y + i*(TOKEN_H/*EIGHT*/+TOKEN_SPACING) << std::endl;
		//_tokenDeque[i+1].visualToken.setRect(TOKENS_X, TOKENS_START_Y + i*(TOKEN_H/*EIGHT*/+TOKEN_SPACING));
	}

	printQueue();

	//each token below the newly placed token must be shifted down on the screen
	shiftTokensDown(i+1);
	
	//*make sure screen is updated at some point in game master after this happens
	releaseActiveToken();
	//activeTokenPtr = NULL;
	return;
}

void TokenQueue::translateToken(CodeToken *tokenPtr, int dx, int dy)
{
  //this translates the token dx and dy
  tokenPtr->visualToken.setRect(tokenPtr->visualToken.getRect().x + dx, tokenPtr->visualToken.getRect().y + dy);
}


void TokenQueue::shiftTokensDown(int index)
{ 
  for (; index < _tokenDeque.size(); index++) {
    translateToken(&(_tokenDeque.at(index)),0, TOKEN_H/*EIGHT*/+TOKEN_SPACING);
    std::cout << "Debug TokenQueue, shiftTokensDown - translating down token number: " << index << std::endl;
  }
  
  printQueue();
  
 return; 
}

void TokenQueue::shiftTokensUp(int index)
{
  for (; index < _tokenDeque.size(); index++) {
    translateToken(&(_tokenDeque.at(index)),0, -TOKEN_H/*EIGHT*/-TOKEN_SPACING);
    std::cout << "Debug TokenQueue, shiftTokensDown - translating down token number: " << index << std::endl;
  }
  
  printQueue();
  
 return; 
}

void TokenQueue::releaseActiveToken() 
{
	if (activeTokenPtr) {
	delete(activeTokenPtr);
	activeTokenPtr = NULL;
	}
	return;
}

void TokenQueue::updateScreen(SDL_Surface *screen)
{
 //put all tokens on screen by going through the queue
 SDL_Surface *newSurface;
 SDL_Rect newRect;
 
 for (int i=0; i < _tokenDeque.size(); i++) {
     newSurface = _tokenDeque[i].visualToken.getSurface();
     newRect = _tokenDeque[i].visualToken.getRect();

     SDL_BlitSurface( newSurface, NULL, screen, &newRect );
  }
  
    if (activeTokenPtr)   SDL_BlitSurface( (*activeTokenPtr).visualToken.getSurface(), NULL, screen,&( (*activeTokenPtr).visualToken.getRect() ));

  
  printQueue();
  
  return;
}