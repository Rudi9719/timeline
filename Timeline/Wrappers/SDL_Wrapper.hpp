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
    SDL_Rect* renderCard(int x, int y);
    void moveCard(int xTransform, int yTransform, SDL_Rect* card);
    void biltSurface(SDL_Surface* newSurface);
    int quit();
    
    
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    
    
private:
    int frame_rate;
    int card_height;
    int card_width;
    int height;
    int width;
    SDL_Surface* mainSurface;
};


#endif /* SDL_Wrapper_hpp */
