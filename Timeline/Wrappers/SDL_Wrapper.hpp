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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "../Classes/Card.hpp"
#include "../Classes/Timer.hpp"


class SDL_Wrapper {
public:
    // Should the screen refresh (redraw)
    bool refreshScreen = false;
    // Should the program quit
    bool quit = false;
    // Is the program in debugging mode
    bool debug = true;
    int clients = 0;
    
    // Create a SDL Wrapper with height/width of window
    SDL_Wrapper(int h, int w);
    SDL_Wrapper();
    
    // Load an image and get a SDL_Surface pointer to it - Depreciated?
    SDL_Surface* loadImage(const char* path);
    // Render a card TODO: Return a card class instead of SDL_Rect
    Card* renderCard(int x, int y);
    
    // Should the program allow connections
    bool allowConnections(TCPsocket sock);
    
    // NetSync message
    char* netSync();
    // Handle click at (X, Y)
    void handleClick(int x, int y);
    // Display message at x, y, with a height of h
    void displayText(const char* message, int x, int y, int h);
    void displayText(const char* message, int x, int y, int h, SDL_Color c);
    // set a SDL_Rect's colour based on RGB
    void colorizeCard(SDL_Rect* card, int r, int g, int b);
    void colorizeCard(Card* card, int r, int g, int b);
    void colorizeCard(Card* card, int preset);
    // Move card by xTransform and yTransform NOT TO (x, y)
    void moveCard(int xTransform, int yTransform, SDL_Rect* card);
    void moveCard(int xTransform, int yTransform, Card card);
    // Snyc FPS
    void syncFPS();
    
    
    
    
    // Start FPS Called Automatically.
    void startFPS();
    // Close the program down and return the error/ok status
    int teardown();
    

private:
    
    std::vector<Card> placedCards = *new std::vector<Card>;
    Timer fpsLimiter;
    int frame_rate = 1;
    int frame = 0;
    int card_height = 100;
    int card_width = 80;
    int height = 0;
    int width = 0;
    
    int activity = 0;
    IPaddress* ip;
    int NET_MAXLEN = 1024;
    
    SDLNet_SocketSet socket = SDLNet_AllocSocketSet(5);
    TCPsocket Server_socket;
    TCPsocket client_sock[5];
    void reDrawCards();
    SDL_Surface* mainSurface = NULL;
    SDL_Window* mainWindow = NULL;
    SDL_Renderer* mainRenderer;// = NULL;
    
    bool init(SDL_Window* window, SDL_Surface* screenSurface, int width, int height);
    
    
};


#endif /* SDL_Wrapper_hpp */
