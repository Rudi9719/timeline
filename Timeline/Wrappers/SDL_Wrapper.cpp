//
//  SDL_Wrapper.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "SDL_Wrapper.hpp"


// Default constructor, loads a window with height and width
SDL_Wrapper::SDL_Wrapper(int h, int w){
    SDL_ClearError();
    this->height = h;
    this->width = w;
    if (!init(this->mainWindow, this->mainSurface, this->width, this->height)) {
        if (this -> debug)
            std::cout << "Something went wrong with initializing the SDL Library" << std::endl;
    } else {
        
        TTF_Init();
        this -> mainRenderer = SDL_CreateRenderer(this -> mainWindow, -1, SDL_RENDERER_ACCELERATED);
        
        SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mainRenderer);
        SDL_RenderPresent(mainRenderer);
        
    }
    
}
void SDL_Wrapper::displayText(const char* message, int x, int y, int h) {
    SDL_ClearError();
    int height = h;
    SDL_Color white = {255, 255, 255};
    TTF_Font* sans = TTF_OpenFont("assets/Sans.ttf", height);
    SDL_Surface* messageSurface = TTF_RenderText_Solid(sans, message, white);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(this -> mainRenderer, messageSurface);
    SDL_Rect messageRect;
    messageRect.x = x;
    messageRect.y = y;
    messageRect.w = ((int) strlen(message) * (height / 2));
    messageRect.h = height;
    
    SDL_RenderCopy(this -> mainRenderer, messageTexture, NULL, &messageRect);
    SDL_RenderPresent(this -> mainRenderer);
    if (this -> debug)
        printf("Error: %s\n", SDL_GetError());
    
}

SDL_Rect SDL_Wrapper::renderCard(int x, int y) {
    SDL_ClearError();
    SDL_Rect r1;
    r1.x = x;
    r1.y = y;
    r1.w = card_width;
    r1.h = card_height;
    SDL_SetRenderDrawColor( this -> mainRenderer, 200, 200, 200,255);
    SDL_RenderFillRect(this -> mainRenderer, &r1);
    SDL_RenderPresent(this -> mainRenderer);
    if (this -> debug)
        printf("Error: %s\n", SDL_GetError());
    return r1;
    
    
}




void SDL_Wrapper::colorizeCard(SDL_Rect* card, int r, int g , int b) {
    SDL_ClearError();
    SDL_SetRenderDrawColor(this -> mainRenderer, r, g, b, 255 );
    SDL_RenderFillRect(this -> mainRenderer, card);
}
void SDL_Wrapper::moveCard(int xTransform, int yTransform, SDL_Rect* card) {
    SDL_ClearError();
    card -> x = (card -> x) - xTransform;
    card -> y = (card -> y) - yTransform;
    
}

void SDL_Wrapper::startFPS() {
    
    this -> fpsLimiter.start();
}
void SDL_Wrapper::syncFPS() {
    this -> frame++;
    if((this -> fpsLimiter.get_ticks() < 1000/frame_rate))
    {
        SDL_Delay((1000/frame_rate)-fpsLimiter.get_ticks());
        if (this -> debug)
            std::cout << "delaying for " << (1000/frame_rate)- fpsLimiter.get_ticks() << " ms" << std::endl;
    }
    SDL_RenderPresent(this -> mainRenderer);
}


void SDL_Wrapper::biltSurface(SDL_Surface* newSurface) {
    SDL_BlitSurface(newSurface, NULL, mainSurface, NULL);
    SDL_UpdateWindowSurface(mainWindow);
}

// Loads an image from path and returns surface
SDL_Surface* SDL_Wrapper::loadImage(const char* path) {
    SDL_Surface* imageSurface = IMG_Load(path);
    if (imageSurface == NULL) {
        std::cout << "Something went wrong loading your image." << std::endl;
        if (this -> debug)
            printf("Error: %s\n", SDL_GetError());
    }
    
    return imageSurface;
}

// Quits and closes libraries
int SDL_Wrapper::quit(){
    IMG_Quit();
    SDL_DestroyWindow(this->mainWindow);
    SDL_Quit();
    return 0;
}

// Check if window can open and populates
bool SDL_Wrapper::init(SDL_Window* window, SDL_Surface* screenSurface, int width, int height) {
    // Initialization! :D
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        return false;
    } else {
        IMG_Init(IMG_INIT_JPG);
        // Make a window!
        window = SDL_CreateWindow("Timeline", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            return false;
        } else {
            // Pass the window back to mainWindow on success
            this -> mainWindow = window;
            return true;
        }
    }
    
    return false;
    
}
