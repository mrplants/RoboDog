/*
  main.cpp
  Sean Fitzgerald, Jon Gautsch, Daniel Tamaru, Maribeth Rauh
 
  Final Project CSE 20212 Spring 2013
 
  An instance of the game's main class, GameMaster, is made and the play function, which begins the game loop,
  is called.
  
  */


#include <iostream>
#include "GameMaster.h"

int main (int argc, char * args[])
{
	//Create an instance of the class that encompasses the whole program
	GameMaster testGame;
	
	//Begin the actual game
	testGame.play();

	return 0;
}
