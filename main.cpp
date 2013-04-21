/*
 Sean Fitzgerald, Jon Gautsch, Daniel Tamaru, Maribeth Rauh
 
 Final Project CSE 20212 Spring 2013
 
 Main.cpp - used to initialize the Master UI and Game Control class
 */


#include <iostream>
#include "GameMaster.h"

int main (int argc, char * args[])
{
  //create an instance of the master game class
    GameMaster testGame;
    std::cout << "Let's play!" << std::endl;
  //tell the master game class instance to play
    testGame.play();

  return 0;
}
