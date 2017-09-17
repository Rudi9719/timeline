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
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "Timer.hpp"


class SDL_Wrapper {
public:

    bool debug = true;
    
    
    SDL_Wrapper(int h, int w);
    SDL_Surface* loadImage(const char* path);
    SDL_Rect renderCard(int x, int y);
    
    void displayText(const char* message, int x, int y, int h);
    void colorizeCard(SDL_Rect* card, int r, int g, int b);
    void moveCard(int xTransform, int yTransform, SDL_Rect* card);
    void syncFPS();
    void startFPS();
    
    int quit();
    

private:
    
    Timer fpsLimiter;
    int frame_rate = 15;
    int frame = 0;
    int card_height = 100;
    int card_width = 80;
    int height = 0;
    int width = 0;
    
    SDL_Surface* mainSurface = NULL;
    SDL_Window* mainWindow = NULL;
    SDL_Renderer* mainRenderer = NULL;
    
    bool init(SDL_Window* window, SDL_Surface* screenSurface, int width, int height);
    
    
};


#endif /* SDL_Wrapper_hpp */
