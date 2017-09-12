//
//  SDL_Wrapper.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "SDL_Wrapper.hpp"

bool init(SDL_Window* window, SDL_Surface* screenSurface, int width, int height);


// Default constructor, loads a window with height and width
SDL_Wrapper::SDL_Wrapper(int h, int w){
        this->height = h;
        this->width = w;
        if (!init(this->mainWindow, this->mainSurface, this->width, this->height)) {
                std::cout << "Something went wrong with initializing the SDL Library" << std::endl;
        } else {

        }

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
