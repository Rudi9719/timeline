//
//  SDL_Wrapper.hpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef SDL_Wrapper_hpp
#define SDL_Wrapper_hpp

#include<string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include<sstream>
#include "../Classes/Card.hpp"
#include "../Classes/Timer.hpp"
#include "../Classes/Sound.hpp"
#include "../Classes/Deck.hpp"
#include "../Classes/Player.hpp"
#include "../Classes/Market.hpp"

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

    // Load an image and get a SDL_Surface pointer to it - Depreciated?
    SDL_Surface* loadImage(const char* path);
    // Render a card TODO: Return a card class instead of SDL_Rect
    Card* renderCard(int x, int y);

    //void displayStartCard();
    //void displayEndCard();

    //clear screen in prep for next frame
    void clearScreen(int r,int g,int b,int opac);

    //displays the entire vector deck of cards
    void displayCards();

    void displayStaticCards();

    int getWindowHeight();
    int getWindowWidth();

    // Should the program allow connections
    bool allowConnections(TCPsocket sock);

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
    void shiftCardColumn (int column);
    void cardPlacer (int mousex, int mousey);
    // Snyc FPS
    void syncFPS();
	//send Msg;
	void sendPacket(std::string Msg);
	//receiving thread
	static int thread_func_wrapper(void* data);
	int receivingThread(void);




    // Start FPS Called Automatically.
    void startFPS();
    // Close the program down and return the error/ok status
    int teardown();


private:

    Market sharedMarket = Market();
    Player players[5]= {
        Player(0, 0, &sharedMarket),
        Player(0, 0, &sharedMarket),
        Player(0, 0, &sharedMarket),
        Player(0, 0, &sharedMarket),
        Player(0, 0, &sharedMarket)
    };
    Sound sound;
    int deck_pos = 0;

    Deck* cardDeck_paths = new Deck();
    std::vector<Card> cardDeck = std::vector<Card>(47);
    std::vector<Card> placedCards;
    Timer fpsLimiter;
    int frame_rate = 60;
    int frame = 0;
    int card_height = 100;
    int card_width = 80;
    int height = 0;
    int width = 0;

    void reDrawCards();
    SDL_Surface* mainSurface = NULL;
    SDL_Window* mainWindow = NULL;
    SDL_Renderer* mainRenderer = NULL;

    bool init(SDL_Window* window, SDL_Surface* screenSurface, int width, int height);
	//Networking vars
	bool yourTurn = false;
	SDLNet_SocketSet Client_set = SDLNet_AllocSocketSet(1);
	char Msg[1024];
	int Your_num;
	int Len;
	bool running = true;
	int timeout = 0;
	int i = 0;
	IPaddress Server_IP;
	std::string Message;
	std::string token;
	std::string arr[4];
	std::string x_str;
	std::string y_str;
	TCPsocket tcpsock;
	SDL_Thread *thread;
	int threadReturnValue;
};


#endif /* SDL_Wrapper_hpp */
