//
//  SDL_Program.cpp
//  Coding Game
//
//  Created by Maribeth Rauh on 3/29/13.
//

#include "SDL_Program.h"

SDL_Program::SDL_Program() {
        std::cout << "Debug SDL_Program.cpp Line: 11 - SDL_Program Constructor start\n" << std::endl;



        std::cout << "Debug SDL_Program.cpp Line: 12 - SDL_Program Constructor end\n" << std::endl;


}

//takes single filename, opens and returns a font
TTF_Font * SDL_Program::loadFont( std::string filename, int size ) {
    //Open the font
    TTF_Font *font;
    font = TTF_OpenFont(filename.c_str(), size);
    
    //If everything loaded fine
    return font;
}

//takes single filename, loads image, optimizes it to screen and returns it
SDL_Surface * SDL_Program::loadImage(std::string filename) {
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;
    
    loadedImage = IMG_Load(filename.c_str());
    
    if (loadedImage != NULL) {
	std::cout << "passed if using filename " << filename << std::endl;
        optimizedImage = SDL_DisplayFormat(loadedImage);
	std::cout << "SDL_DisplayFormat successful" << std::endl;
        SDL_FreeSurface(loadedImage);
        
        //Map the color key
        if (optimizedImage != NULL) {
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
            
            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
    
    //used if class has a deque of the surfaces in it
    //blocks.push_front(optimizedImage);
    
    return optimizedImage;
}

//creates an SDL_Rect that corresponds to an image (SDL_Surface)
SDL_Rect SDL_Program::createRect(SDL_Surface * image, int startX, int startY) {
    SDL_Rect rect;
    rect.w = image->w;
    rect.h = image->h;
    
    // will be updated when apply_surface called
    rect.x = startX;
    rect.y = startY;
    
    return rect;
}

//NOTE: No parameters needed-
//		rect will be data member of class being called on
//		x and y will be taken directly from the mouse
//checks if the mouse is located within the perimeter of the image (whose associated rect is passed in)

bool SDL_Program::mouseOverImage(SDL_Rect imageRect, int x, int y) {
    if (x > imageRect.x && x < (imageRect.x + imageRect.w) && y > imageRect.y && y < (imageRect.y + imageRect.h)) {
        return true;
    }else{
        return false;
    }
}