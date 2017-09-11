//
//  SDL_Wrapper.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "SDL_Wrapper.hpp"

SDL_Wrapper::SDL_Wrapper(int h, int w){
    this -> height = h;
    this -> width = w;
    
    
}


bool init(SDL_Window* window, SDL_Surface* screenSurface, int width, int height) {
    // Initialization! :D
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        return false;
    } else {
        IMG_Init(IMG_INIT_JPG);
        // Make a window!
        std::cout << "Opening window!" << std::endl;
        window = SDL_CreateWindow("Timeline", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            return false;
        } else {
            // Get the window surface
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            // Update the surface
            SDL_UpdateWindowSurface(window);
            return true;
        }
    }
    
    return false;
    
}
