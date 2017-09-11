//
//  SDL_Wrapper.hpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef SDL_Wrapper_hpp
#define SDL_Wrapper_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>

class SDL_Wrapper {
public:
    
    SDL_Wrapper(int h, int w);
    SDL_Surface* loadImage(const char* path);
    int quit();
    
private:
    int height;
    int width;
    SDL_Window* mainWindow;
    SDL_Surface* mainSurface;
};


#endif /* SDL_Wrapper_hpp */
