//
//  SDL_Program.cpp
//  Coding Game
//
//  Created by Maribeth Rauh on 3/29/13.
//

#include "SDL_Program.h"

SDL_Program::SDL_Program() {}

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
        optimizedImage = SDL_DisplayFormat(loadedImage);
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

//NOTE: only x, y, and destination should be passed in, possibly clip at lower level-
//		offset and source known by class being called on
//blits image to destination at (x, y)
//Parameters 1, 2: x and y coordinates where image will be blitted
//Parameter 3: image to be blitted
//Parameter 4: SDL_Rect associated with the surface being blitted
//Parameter 5: image being blitted onto
//Parameter 6: which clip of source to blit
SDL_Rect applySurface(int x, int y, SDL_Surface *source, SDL_Rect offset, SDL_Surface *destination, SDL_Rect *clip) {
    offset.x+=x;
    offset.y+=y;
    
    SDL_BlitSurface( source, clip, destination, &offset );
    return offset;
}

//NOTE: No parameters needed-
//		rect will be data member of class being called on
//		x and y will be taken directly from the mouse
//checks if the mouse is located within the perimeter of the image (whose associated rect is passed in)
bool mouseOverImage(SDL_Rect imageRect, int x, int y) {
    if (x > imageRect.x && x < (imageRect.x + imageRect.w) && y > imageRect.y && y < (imageRect.y + imageRect.h)) {
        return true;
    }else{
        return false;
    }
}