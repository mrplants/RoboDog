//Contains all constants throughout program

#ifndef _CONSTANTS
#define _CONSTANTS

//Screen attributes
    #define SCREEN_WIDTH 640
    #define SCREEN_HEIGHT 480
    #define SCREEN_BPP 32
    
    #define TOKEN_PANE_PERCENT_W 176/640
    #define TOKEN_PANE_W 176
    #define TOKEN_PANE_PERCENT_H 1
    //the height of the token pane is the height of the screen
    
    #define TOKENS_START_Y 10 //pixels
    #define TOKENS_X 10 //all tokens will be lined up 10 px in from the left side
    
    #define TOKEN_SPACING 5 //pixels between tokens
    #define TOKEN_HEIGHT 50 //no token image can be taller than this
    
    #define TOKEN_LIB_PERCENT_W (1-TOKEN_PANE_PERCENT_W)
    #define TOKEN_LIB_W 464
    #define TOKEN_LIB_PERCENT_H 150/640
    #define TOKEN_LIB_H 150
    #define TOKEN_LIB_START_X 640-TOKEN_LIB_W
    
    #define TOKEN_STACK_W 89
    #define TOKEN_STACK_H 58

    // dimensions of Mario
    #define MARIO_WIDTH 184;
    #define MARIO_HEIGHT 200;

    // Mario action statuses
    #define MARIO_STAND 0;
    #define MARIO_STEP 1;
    #define MARIO_JUMP 2;
    #define MARIO_TURN 3;
    #define MARIO_KICK 4;

#endif //_CONSTANTS defined
