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

class Timer
{
private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;
    
public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    
    int get_ticks();
    
    bool is_started();
    bool is_paused();
};

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    started = false;
    paused = false;
}

void Timer::pause()
{
    if((started==true)&&(paused==false))
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if(paused==true)
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    if(started==true)
    {
        if(paused==true)
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

class SDL_Wrapper {
public:
    
    bool debug = false;
    SDL_Wrapper(int h, int w);
    SDL_Surface* loadImage(const char* path);
    SDL_Rect* renderCard(int x, int y);
    //void colorizeCard(SDL_Rect* card, )
    void moveCard(int xTransform, int yTransform, SDL_Rect* card);
    void biltSurface(SDL_Surface* newSurface);
    void syncFPS();
    int quit();
    
    
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    
    
private:
    Timer fpsLimiter;
    int frame_rate = 15;
    int frame = 0;
    int card_height = 100;
    int card_width = 80;
    int height;
    int width;
    SDL_Surface* mainSurface;
};


#endif /* SDL_Wrapper_hpp */
