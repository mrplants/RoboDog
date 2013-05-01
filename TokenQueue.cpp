/*
  TokenQueue.cpp
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  Allows for easy access to ordering tokens in the UI
  As tokens are added to the token-train, their pointers are inserted or added into the deque
  When the code is ready to be interpretted and run, this queue is dispatched to the interpreter and executed
    
  Composed classes:
    CodeToken - the individual token component
  */

#include "TokenQueue.h"

#pragma mark -
#pragma Destructor and Constructor

//constructor
TokenQueue::TokenQueue()
{
	activeTokenPtr = NULL;
}

//destructor
TokenQueue::~TokenQueue() {}

#pragma mark -
#pragma mark Methods About Changing the Queue

//adds a token to the end of the tokenQueue
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
 
//removes the token at the specified index and deletes it from memory if the token is a loop, it deletes both loop tokens
void TokenQueue::removeTokenAtIndex(int index)
{
	if (!_tokenDeque[index]._commandID.compare("open_loop") || !_tokenDeque[index]._commandID.compare("close_loop")) {
		//save the loop ID number so that you can take out all the blocks with that ID number
		int uniqueLoopID = _tokenDeque[index]._uniqueLoopID;

		//delete the two (start and end) loop tokens with that ID number
		for (int i = 0; i < _tokenDeque.size(); i++) {
		  
			if (_tokenDeque[i]._uniqueLoopID == uniqueLoopID) {
				_tokenDeque.erase(_tokenDeque.begin() + i);
				shiftTokensUp(i);
				i = -1;
			}
		}
	}else{
		_tokenDeque.erase(_tokenDeque.begin() + index);
		shiftTokensUp(index);
	}
}

//NOT USING NAMESPACE - helper function only
bool pointIsInNumberRect(int x, int y, int rectX, int rectY)
{
  if (x > (rectX + 73) && x < (rectX + 93) && y > (rectY + 12) && y < (rectY + 26)) return true;
  return false;
}

//checks if the mouse was clicked over an existing token or one in the library
bool TokenQueue::mouseOverToken(int x, int y)
{
	//iterate through all existing tokens to see if the mouse was clicked on one
	//make that token active if so
	for (int i=0; i < _tokenDeque.size(); i++) {
	  
		if (_tokenDeque[i].visualToken.mouseOverImage(_tokenDeque[i].visualToken.getRect(), x, y)) {
		  
		    if (!_tokenDeque[i]._commandID.compare("open_loop")) {
			if (pointIsInNumberRect(x, y, _tokenDeque[i].visualToken.getRect().x, _tokenDeque[i].visualToken.getRect().y)) {
				
				if (_tokenDeque[i]._repeatNumber <= 5) {
					_tokenDeque[i]._repeatNumber++;
					_tokenDeque[i].visualToken._repeatNumber++;
				}else{
					_tokenDeque[i]._repeatNumber = 1;
					_tokenDeque[i].visualToken._repeatNumber = 1;
				}
				//add one to the visual representation. Don't worry, if it goes over 5, it will reset at 1.
				return false;
			}
		    }
		    activeTokenPtr = new CodeToken(_tokenDeque[i]);
		    
		    removeTokenAtIndex(i);
		    
		    if(!activeTokenPtr->_commandID.compare("close_loop")) {
			
			CodeToken tempCodeToken("open_loop");
			tempCodeToken._uniqueLoopID = activeTokenPtr->_uniqueLoopID;
			tempCodeToken._repeatNumber = activeTokenPtr->_repeatNumber;
			tempCodeToken.visualToken.tokenRect = activeTokenPtr->visualToken.tokenRect;
			activeTokenPtr = new CodeToken(tempCodeToken);
		    }
		    return true;
		}
		
	}
  
	//if none was made active, check if the mouse clicked in the library
	//potentially make a new token if so
	if (overTokenStack(x, y, 0)) {
	  //instantiate loop token
	  newToken("step",  TOKEN_LIB_START_X+(0)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	  
	}else if (overTokenStack(x, y, 1)) {
	  //instantiate step token
	  newToken("turn",  TOKEN_LIB_START_X+(1)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	  
	}else if (overTokenStack(x, y, 2)) {
	  //instantiate jump token
	  newToken("kick",  TOKEN_LIB_START_X+(2)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	  
	}else if (overTokenStack(x, y, 3)) {
	  //instantiate kick token
	  newToken("jump",  TOKEN_LIB_START_X+(3)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	  
	}else if (overTokenStack(x, y, 4)) {
	  //instantiate turn token
	  newToken("open_loop", TOKEN_LIB_START_X+(4)*TOKEN_STACK_W, TOKEN_STACK_Y);
	  return true;
	}
	
	return false;
}

//checks if the mouse is over one of the stacks of tokens
bool TokenQueue::overTokenStack(int x, int y, int i) 
{
	if (x > TOKEN_LIB_START_X+i*TOKEN_STACK_W && x < TOKEN_LIB_START_X+(i+1)*TOKEN_STACK_W) {
	  if (y > SCREEN_HEIGHT-TOKEN_LIB_H && y < SCREEN_HEIGHT) {
	    return true;
	  }
	}
	return false; 
}

//instantiates a new token based on where the user clicked
void TokenQueue::newToken(std::string commandID, int x, int y)
{
	CodeToken newToken(commandID);

	newToken.visualToken.setRect(x, y);
	newToken._commandID = commandID;

	if(commandID.compare("open_loop")) {
	// This token is not a loop so we set their repeat number and loop ID to -1
		newToken._repeatNumber = -1;
		newToken._uniqueLoopID = -1;
	
	}else { //this token IS a loop token
		newToken._repeatNumber = 1;
		newToken.visualToken._repeatNumber = 1;

		//get a unique loop ID by parsing all the other loop tokens
		int uniqueLoopID = 0;
		for (int i = 0; i < _tokenDeque.size(); i++) {
		  
			if (!_tokenDeque[i]._commandID.compare("open_loop") || !_tokenDeque[i]._commandID.compare("close_loop")) {
			  while (uniqueLoopID == _tokenDeque[i]._uniqueLoopID) {uniqueLoopID++; i = -1;} //oops, this unique ID is taken by some other loop
			}
		}
		newToken._uniqueLoopID = uniqueLoopID;
		
	}
	activeTokenPtr = new CodeToken(newToken);
	return;
}

#pragma mark -
#pragma mark Methods About Accessing the Queue

//------------These are the token identifiers. If you use other identifiers, it wont work.-------------- 
//1 - "step"
//2 - "jump"
//3 - "turn"
//4 - "kick"
//5 - "open_loop"
//6 - "close_loop"
//------------------------------------------------------------------------------------------------------

//makes the 2D vector that will be passed to the interpreter out of the deque of tokens
std::vector<std::vector<int> > TokenQueue::getInterpreterVector()
{
	// the vector with the interpreters commands
	std::vector<std::vector<int> > returnVector;

	// loops throught he tokens and adds their identifiers to the vector
	for(int i = 0; i < _tokenDeque.size(); i++) {
		std::vector<int> tokenVectorOfIdentifiers;

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
	}
	return returnVector;
}

//returns a reference to the token at the specified index
CodeToken TokenQueue::getTokenAtIndex(int index)
{
	return _tokenDeque.at(index);
}

//returns a reference to the token at the specified index
CodeToken TokenQueue::operator[](int index)
{
	return _tokenDeque.at(index);
}

//returns a constant reference to the token at the specified index
const CodeToken TokenQueue::TokenQueue::operator[](int index) const
{
	return _tokenDeque.at(index);
}

//prints out the commandID and x and y coordinate of every token in the deque
void TokenQueue::printQueue()
{
	for (int i=0; i < _tokenDeque.size(); i++) {
		std::cout << i << " " << _tokenDeque[i]._commandID << ": " << _tokenDeque[i].visualToken.getRect().x << ", " << _tokenDeque[i].visualToken.getRect().y << std::endl;
	}
	return; 
}

#pragma mark -
#pragma mark Methods About Manipulating Tokens on the Screen

//if there is an active token, its rect is moved by the relative positions passed in
void TokenQueue::translateActiveToken(int dx, int dy)
{
	if (activeTokenPtr)
		translateToken(activeTokenPtr, dx, dy);
}

//places the active token in the token pane aligned with the other tokens and shifts those around it appropriately
void TokenQueue::snapActiveToken()
{
	//finds the index of the new active token
	std::deque<CodeToken>::iterator it = _tokenDeque.begin();
	SDL_Rect activeTokenRect = (*activeTokenPtr).visualToken.getRect();
  
	int i;
	for (i = 0; it != _tokenDeque.end(); it++) {
		SDL_Rect currentTokenRect = _tokenDeque[i].visualToken.getRect();
		//when the token that was dropped is above the next token, its spot in the queue has been found
		if (currentTokenRect.y > activeTokenRect.y) {
			break;
		}
		i++;
	}
	_tokenDeque.insert(it, *activeTokenPtr);
	
	//places the newly dropped token on the screen
	//Note: all tokens have the same x coordinate
	_tokenDeque[i].visualToken.setRect(TOKENS_X, TOKENS_START_Y + i*(TOKEN_H/*EIGHT*/+TOKEN_SPACING));
	SDL_Rect tempRect = _tokenDeque[i].visualToken.getRect();


	//if the token is a loop token, then we need to add a close loop underneath it
	if (!(*activeTokenPtr)._commandID.compare("open_loop")) {
	  
		//std::cout << "Debug snapActiveToken Line 330: HOLY SHIT A LOOP TOKEN GETTING PLACED? ARE YOU CRAZY? " << tempRect.x << ", " << tempRect.y << std::endl;

		CodeToken closeLoopToken("close_loop");
		closeLoopToken._uniqueLoopID = (*activeTokenPtr)._uniqueLoopID;
		closeLoopToken._repeatNumber = (*activeTokenPtr)._repeatNumber;
		closeLoopToken.visualToken.setRect(TOKENS_X, TOKENS_START_Y + (i)*(TOKEN_H/*EIGHT*/+TOKEN_SPACING));
		
		//add the close loop token to the deque directly after the open loop
		if (it == _tokenDeque.end()) {
			_tokenDeque.push_back(closeLoopToken);
		}else{
			it++;
			_tokenDeque.insert(it, closeLoopToken);
			shiftTokensDown(i+2);
		}
	}

	//printQueue();

	//each token below the newly placed token must be shifted down on the screen
	shiftTokensDown(i+1);
	
	releaseActiveToken();
	return;
}

void TokenQueue::translateToken(CodeToken *tokenPtr, int dx, int dy)
{
	//this translates the token dx and dy
	tokenPtr->visualToken.setRect(tokenPtr->visualToken.getRect().x + dx, tokenPtr->visualToken.getRect().y + dy);
}

//moves all tokens in the queue below a certain index down
void TokenQueue::shiftTokensDown(int index)
{ 
	for (; index < _tokenDeque.size(); index++) {
		translateToken(&(_tokenDeque.at(index)),0, TOKEN_H+TOKEN_SPACING);
	}
  
	//printQueue();
  
	return; 
}

//moves all the tokens in the queue above a certain index up
void TokenQueue::shiftTokensUp(int index)
{
	for (; index < _tokenDeque.size(); index++) {
		translateToken(&(_tokenDeque.at(index)),0, -TOKEN_H-TOKEN_SPACING);
	}
  
	//printQueue();
  
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

//re-applies all of the tokens in the queue to the screen
void TokenQueue::updateScreen(SDL_Surface *screen)
{
	//put all tokens on screen by going through the queue
	SDL_Surface *newSurface;
	SDL_Rect newRect;
 
	for (int i=0; i < _tokenDeque.size(); i++) {
		newSurface = _tokenDeque[i].visualToken.getSurface();
		newRect = _tokenDeque[i].visualToken.getRect();
		SDL_BlitSurface( newSurface, NULL, screen, &newRect );
		
		if (!_tokenDeque[i]._commandID.compare("open_loop")) {
			newSurface = _tokenDeque[i].visualToken.getNumberSurface();
			newRect = _tokenDeque[i].visualToken.getRect();
			SDL_BlitSurface( newSurface, NULL, screen, &newRect );
		}
	}
  
	//updates the token being dragged (since only those IN the deque were updated before)
	if (activeTokenPtr)
		SDL_BlitSurface( (*activeTokenPtr).visualToken.getSurface(), NULL, screen,&( (*activeTokenPtr).visualToken.getRect() ));

	//updates the position of the number on the for loop
	if (activeTokenPtr && !activeTokenPtr->_commandID.compare("open_loop")) {
		 newSurface = activeTokenPtr->visualToken.getNumberSurface();
		 newRect = activeTokenPtr->visualToken.getRect();
		 SDL_BlitSurface( newSurface, NULL, screen, &newRect );
	}

	//printQueue();

	return;
}