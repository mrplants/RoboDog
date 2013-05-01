/*
  constants.h
  Sean Fitzgerald, Jon Gautsch, Daniel Tamaru, Maribeth Rauh
 
  Final Project CSE 20212 Spring 2013
  
  Contains all constants used throughout program
  */

#ifndef _CONSTANTS
#define _CONSTANTS

    // screen attributes
    #define SCREEN_WIDTH 640
    #define SCREEN_HEIGHT 480
    #define SCREEN_BPP 32
    
    // token dimensions
    #define TOKEN_W (104)
    #define TOKEN_H (39)
    
    // token pane dimensions
    #define TOKEN_PANE_PERCENT_W 176/640
    #define TOKEN_PANE_W 176
    #define TOKEN_PANE_PERCENT_H 1
    //the height of the token pane is the height of the screen
    
    #define TOKENS_START_Y 20 //pixels
    #define TOKENS_X (TOKEN_PANE_W / 2 - TOKEN_W / 2) //all tokens will be lined up in the middle of the pane
    
    #define TOKEN_SPACING 3 //pixels between tokens
    
    // token library dimensions
    #define TOKEN_LIB_PERCENT_W (1-TOKEN_PANE_PERCENT_W)
    #define TOKEN_LIB_W 464 
    #define TOKEN_LIB_PERCENT_H (150/640) 
    #define TOKEN_LIB_H 150 
    #define TOKEN_LIB_START_X (640-TOKEN_LIB_W)
 
    // dimensions of game world portion of screen
    #define GAME_WORLD_H 330
    #define GAME_WORLD_W 464

    // length of the level image
    #define LEVEL_LENGTH 2784
   
    // dimensions of run button
    #define RUN_BUTTON_W 89
    #define RUN_BUTTON_H 58

    // dimensions of enemy
    #define ENEMY_WIDTH 77
    #define ENEMY_HEIGHT 250

    // dimensions of Mario
    #define MARIO_WIDTH 136
    #define MARIO_HEIGHT 97

    // Mario action statuses
    #define MARIO_STAND 0
    #define MARIO_STEP 1
    #define MARIO_JUMP 2
    #define MARIO_TURN 3
    #define MARIO_KICK 4
    
    // dimensions of a stack of tokens
    #define TOKEN_STACK_W ((SCREEN_WIDTH - TOKEN_PANE_W) / 5)
    #define TOKEN_STACK_H (60)
    #define TOKEN_STACK_Y (371)

#endif //_CONSTANTS defined
