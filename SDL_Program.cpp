/*
  SDL_Program.cpp
  BASE CLASS for SDL components of Coding Game
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  This program is a **base class** for the SDL classes our coding game uses.  It provides the basic
  SDL methods that are used by every SDL class such as loadFont, cleanUp, and loadImage and data members
  that are equally essential, such as the screen.
  
  **Abstract so cannot be instantiated
  */

#include "SDL_Program.h"

SDL_Program::SDL_Program() {}

//takes single filename, opens and returns a font
TTF_Font * SDL_Program::loadFont( std::string filename, int size )
{
	//Open the font
	TTF_Font *font;
	font = TTF_OpenFont(filename.c_str(), size);
    
	//If everything loaded fine
	return font;
}

//takes single filename, loads image, optimizes it to screen and returns it
SDL_Surface * SDL_Program::loadImage(std::string filename)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;
    
	loadedImage = IMG_Load(filename.c_str());
    
	if (loadedImage != NULL) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
        
		//Map the color key
		if (optimizedImage != NULL) {
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0x00, 0xFF, 0xFF );
            
			//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}else
			std::cout << "ERR: Image is could not be loaded" << std::endl;
	}
    
    return optimizedImage;
}

//creates an SDL_Rect that corresponds to an image (SDL_Surface)
SDL_Rect SDL_Program::createRect(SDL_Surface * image, int startX, int startY)
{
	SDL_Rect rect;
	
	if (image == NULL)
            std::cout << "ERR: The image is NULL" << std::endl;

	rect.w = image->w;
	rect.h = image->h;
    
	// will be updated when translateToken (or similar) is called
	rect.x = startX;
	rect.y = startY;
    
	return rect;
}


//checks if the mouse is located within the perimeter of the image (whose associated rect is passed in)
bool SDL_Program::mouseOverImage(SDL_Rect imageRect, int x, int y) {
    if (x > imageRect.x && x < (imageRect.x + imageRect.w) && y > imageRect.y && y < (imageRect.y + imageRect.h))
        return true;
    else
        return false;
}
