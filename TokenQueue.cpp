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

std::deque<CodeToken> TokenQueue::getTokenQueue()
{
 return _tokenDeque; 
}

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
	_tokenDeque.erase(_tokenDeque.begin() + index);
}
//removes the token at the specified index and deletes it from memory

void TokenQueue::newToken()
{
	CodeToken newToken;
	_tokenDeque.push_back(newToken);
	*activeToken = _tokenDeque.back();
	return;
}


#pragma mark -
#pragma mark Methods About Accessing the Queue

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
  _tokenDeque.pop_back();
  activeToken = NULL;
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