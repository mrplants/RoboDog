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
	activeToken = NULL;
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
	_tokenDeque.push_back(newToken);
}
//adds a token to the end of the tokenQueue

void TokenQueue::removeTokenAtIndex(int index)
{
  if (_tokenDeque[index]._commandID.compare("open_loop") || _tokenDeque[index]._commandID.compare("close_loop"))
  {
    //save the loop ID number so that you can take out all the blocks with that ID number
    int uniqueLoopID = _tokenDeque[index]._uniqueLoopID;

    //delete the two (start and end) loop tokens with that ID number
    for (int i = 0; i < _tokenDeque.size(); ++i)
    {
      if (_tokenDeque[i]._uniqueLoopID == uniqueLoopID)
          _tokenDeque.erase(_tokenDeque.begin() + i);
    }


  }
  else _tokenDeque.erase(_tokenDeque.begin() + index);
}
//removes the token at the specified index and deletes it from memory if the token is a loop, it deletes both loop tokens

bool TokenQueue::mouseOverToken(int x, int y)
{
	//iterate through all existing tokens to see if the mouse was clicked on one
	//make that token active if so
	for (int i=0; i < _tokenDeque.size(); i++) {
		if (_tokenDeque[i].visualToken.mouseOverImage(_tokenDeque[i].visualToken.getRect(), x, y)) {
		    *activeToken = _tokenDeque[i];
		    return true;
		}
	}
  
  //if none was made active, check if the mouse clicked in the library
  //potentially make a new token if so
  
  return false;
}
//checks if the mouse was clicked over an existing token or one in the library

void TokenQueue::newToken(std::string commandID)
{
  #warning More specifics needed when making a new token since there are different types - FIXED, whoever put this warning, check out the fix and remove the warning if it looks good

	CodeToken newToken;

  newToken._commandID = commandID;

  if(commandID.compare("open_loop")) {
    // This token is not a loop so we set their repeat number and loop ID to -1
    newToken._repeatNumber = -1;
    newToken._uniqueLoopID = -1;
  }
  else {
    newToken._repeatNumber = 0;

    //get a unique loop ID by parsing all the other loop tokens
    int uniqueLoopID = -1;
    for (int i = 0; i < _tokenDeque.size(); i++)
    {
      if (_tokenDeque[i]._commandID.compare("open_loop"))
        uniqueLoopID++; //oops, this unique ID is taken by some other loop;
    }
    uniqueLoopID++; //so that we get a truly unique ID
    newToken._uniqueLoopID = uniqueLoopID;

  }

  #warning Only the open_loop token is pushed with creation.
  #warning When the mouse is released and open_loop is added to the deque, close_loop is added below it.
  #warning To do this, we must also have remove functions such that if you click on either an "open" or a "close", and pull it out, both are removed.


	_tokenDeque.push_back(newToken); //put the token at the back of the deque in the activeToken spot
	activeToken = &(_tokenDeque.back());
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

#warning These are the token identifiers. If you use other identifiers, it wont work. 
#warning Maybe we should #define these somewhere?
//
#warning 1 - "step"
#warning 2 - "jump"
#warning 3 - "turn"
#warning 4 - "kick"
#warning 5 - "open_loop"
#warning 6 - "close_loop"
//

    //store the command ID of the token
    if (_tokenDeque[i]._commandID.compare("step"))
      tokenVectorOfIdentifiers.push_back(1);
    else if (_tokenDeque[i]._commandID.compare("jump"))
      tokenVectorOfIdentifiers.push_back(2);
    else if (_tokenDeque[i]._commandID.compare("turn"))
      tokenVectorOfIdentifiers.push_back(3);
    else if (_tokenDeque[i]._commandID.compare("kick"))
      tokenVectorOfIdentifiers.push_back(4);
    else if (_tokenDeque[i]._commandID.compare("open_loop"))
      tokenVectorOfIdentifiers.push_back(5);
    else if (_tokenDeque[i]._commandID.compare("close_loop"))
      tokenVectorOfIdentifiers.push_back(6);

    //store the loop identifier
    tokenVectorOfIdentifiers.push_back(_tokenDeque[i]._uniqueLoopID);

    //store the number of repeats in the loop
    tokenVectorOfIdentifiers.push_back(_tokenDeque[i]._repeatNumber);

    //store the tokens identifiers to the vector<vector<int> >
    returnVector.push_back(tokenVectorOfIdentifiers);
  }
  return returnVector;
}

//-----------------------------------------------------------------------------------------------------
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

#pragma mark -
#pragma mark Methods About Manipulating Tokens on the Screen

void TokenQueue::translateActiveToken(int dx, int dy)
{
  //update the rect of the active surface 
  SDL_Rect rect = (*activeToken).visualToken.getRect();
  rect.x += dx;
  rect.y += dy;
  (*activeToken).visualToken.setRect(rect.x, rect.y);
  
  return;
}

void TokenQueue::snapActiveToken()
{
  //finds the index of the new active token
  std::deque<CodeToken>::iterator it = _tokenDeque.begin();
  SDL_Rect activeTokenRect = (*activeToken).visualToken.getRect();
  
  int i;
  for (i = 0; it != _tokenDeque.end(); it++) {
    
    SDL_Rect currentTokenRect = _tokenDeque[i].visualToken.getRect();
    //when the token that was dropped is above the next token, its spot in the queue has been found
    if (currentTokenRect.y > activeTokenRect.y) {
      break;
    }
    i++;
  }
    _tokenDeque.insert(it, *activeToken);

    //if the token is a loop token, then we need to add a close loop underneath it
    if ((*activeToken)._commandID.compare("open_loop"))
    {
      CodeToken closeLoopToken;
      closeLoopToken._commandID = "close_loop";
      closeLoopToken._uniqueLoopID = activeToken->_uniqueLoopID;
      closeLoopToken._repeatNumber = activeToken->_repeatNumber;
      it++;
      _tokenDeque.insert(it, closeLoopToken);
    }
  
  //places the newly dropped token on the screen
  //Note: all tokens have the same x coordinate
  _tokenDeque[i].visualToken.setRect(TOKENS_X, TOKENS_START_Y + i*(TOKEN_HEIGHT+TOKEN_SPACING));

  //each token below the newly placed token must be shifted down on the screen
  shiftTokens(i+1);
  //make sure screen is updated at some point in game master after this happens
  releaseActiveToken();
  return;
}

void TokenQueue::shiftTokens(int index)
{ 
  for (; index < _tokenDeque.size(); index++) {
    activeToken = &(_tokenDeque.at(index));
    translateActiveToken(0, TOKEN_HEIGHT+TOKEN_SPACING);
  }
 return; 
}

void TokenQueue::releaseActiveToken() 
{
  if (activeToken) {
    _tokenDeque.pop_back();
    activeToken = NULL;
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
  
  return;
}