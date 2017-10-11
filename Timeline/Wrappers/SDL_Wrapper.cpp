//
//  SDL_Wrapper.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "SDL_Wrapper.hpp"


// Wrapper constructor, loads a window with height and width
SDL_Wrapper::SDL_Wrapper(int h, int w){
    SDL_ClearError();
    this->height = h;
    this->width = w;
    if (!init(this->mainWindow, this->mainSurface, this->width, this->height)) {
        if (this -> debug)
            std::cout << "Something went wrong with initializing the SDL Library" << std::endl;
    } else {
        
        TTF_Init();
        SDLNet_Init();
        this -> mainRenderer = SDL_CreateRenderer(this -> mainWindow, -1, SDL_RENDERER_ACCELERATED);
        
        SDL_SetRenderDrawColor(this -> mainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(this -> mainRenderer);
        SDL_RenderPresent(this -> mainRenderer);
        
    }
    
    Card* helpCard = this -> renderCard(width - 25, 0);
    helpCard -> setCardType(9);
    this -> colorizeCard(helpCard, 247132000);
    this -> displayText("Help", width - 60, 10, 30);
    this -> startFPS();
    
}

// Default SDL Wrapper creation
SDL_Wrapper::SDL_Wrapper() {
    int height = 850;
    int width = 1000;
    SDL_Wrapper(height, width);
}

// Displays message at x and y, using height and defaults to white
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
    this -> refreshScreen = true;
    
    if (this -> debug)
        printf("Error: %s\n", SDL_GetError());
    
}

// Displays message at x and y, using height and an SDL Color
void SDL_Wrapper::displayText(const char* message, int x, int y, int h, SDL_Color c) {
    SDL_ClearError();
    int height = h;
    TTF_Font* sans = TTF_OpenFont("assets/Sans.ttf", height);
    SDL_Surface* messageSurface = TTF_RenderText_Solid(sans, message, c);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(this -> mainRenderer, messageSurface);
    SDL_Rect messageRect;
    messageRect.x = x;
    messageRect.y = y;
    messageRect.w = ((int) strlen(message) * (height / 2));
    messageRect.h = height;
    
    SDL_RenderCopy(this -> mainRenderer, messageTexture, NULL, &messageRect);
    this -> refreshScreen = true;
    
    if (this -> debug)
        printf("Error: %s\n", SDL_GetError());
    
}


// Allow new connections: Andrew
bool SDL_Wrapper::allowConnections(TCPsocket sock) {
    if (this -> client_sock[0] != NULL) {
        if (this -> clients <= 5) {
            SDLNet_TCP_AddSocket(this -> socket, sock);
            this -> client_sock[clients] = sock;
            clients++;
            SDLNet_TCP_Send(sock, "WELCOME!", 8);
            return true;
            
        } else {
            SDLNet_TCP_Send(sock, "NO_ROOM", 8);
            SDLNet_TCP_Close(sock);
        }
    }
    return false;
}

// Sync networking: Andrew
char* SDL_Wrapper::netSync() {
    char* message = NULL;
    while (SDLNet_CheckSockets(socket, 0) > 0) {
        for (int i = 0; i < this -> clients; i++) {
            if (SDLNet_SocketReady(client_sock[i])) {
                SDLNet_TCP_Recv(client_sock[i], message, this-> NET_MAXLEN);
                
                if (strcmp(message, "quit") || strcmp(message,"shutdown")) {
                    // delete socket of client and open it up to new client
                    if (strcmp(message, "shutdown")) {
                        this -> quit = true;
                    }
                }
                else
                {
                    //send all data recieve from client I to all clients except I
                    for (int k = 0; k < this -> clients; k++) {
                        if (k != i) {
                            SDLNet_TCP_Send(client_sock[k], message, (int) strlen(message) + 1);
                        }
                    }
                }
            }
        }
        
    }
    this -> refreshScreen = true;
    return message;
}

// Determines if a placed card owns a click
// If yes, it delegates control to the card.
// Else it renders a new card at x/y and sets
//      type to 0.
void SDL_Wrapper::handleClick(int x, int y) {
    bool clickOwned = false;
    for(Card card : placedCards) {
        std::cout << card.getCardType() << std::endl;
        if (card.cardButton.ownsClick(x, y)) {
            card.handleClick(x, y);
            clickOwned = true;
        }
    }
    if (!clickOwned) {
        Card* newCard = renderCard(x, y);
        newCard -> setCardType(0);
    }
}


// Renders a card and pushes it back to the placedCards,
//      then refreshes the screen
// returns a pointer to the card rendered
Card* SDL_Wrapper::renderCard(int x, int y) {
    SDL_ClearError();
    
    SDL_Rect r1;
    r1.x = x - this -> card_width / 2;
    r1.y = y - this -> card_height / 2;
    r1.w = card_width;
    r1.h = card_height;
    Card c = Card(r1);
    SDL_SetRenderDrawColor( this -> mainRenderer, 200, 200, 200,255);
    SDL_RenderFillRect(this -> mainRenderer, &r1);
    if (this -> debug)
        printf("%s\n", SDL_GetError());
    this -> refreshScreen = true;
    this -> placedCards.push_back(c);
    Card* ret = &c;
    return ret;
    
    
}



// Color a SDL_Rect using RGB
void SDL_Wrapper::colorizeCard(SDL_Rect* card, int r, int g , int b) {
    SDL_ClearError();
    SDL_SetRenderDrawColor(this -> mainRenderer, r, g, b, 255 );
    SDL_RenderFillRect(this -> mainRenderer, card);
    this -> refreshScreen = true;
}
// Color a card using RGB
void SDL_Wrapper::colorizeCard(Card* card, int r, int g , int b) {
    SDL_ClearError();
    SDL_SetRenderDrawColor(this -> mainRenderer, r, g, b, 255 );
    SDL_RenderFillRect(this -> mainRenderer, &card -> cardRect);
    this -> refreshScreen = true;
}
// Color a card using a preset color
void SDL_Wrapper::colorizeCard(Card* card, int preset) {
    int r = 0;
    int b = 0;
    int g = 0;
    switch(preset) {
        case 247132000:
            r = 247;
            b = 132;
            g = 0;
            break;
        default:
            break;
    }
    SDL_ClearError();
    SDL_SetRenderDrawColor(this -> mainRenderer, r, g, b, 255 );
    SDL_RenderFillRect(this -> mainRenderer, &card-> cardRect);
    this -> refreshScreen = true;
}


// Move a card and it's UIButton then refresh the screen
void SDL_Wrapper::moveCard(int xTransform, int yTransform, Card card) {
    SDL_ClearError();
    card.moveCard(xTransform, yTransform);
    this -> refreshScreen = true;
}

// Start FPS limiter
void SDL_Wrapper::startFPS() {
    
    this -> fpsLimiter.start();
}

// Sync fps using frame rate from header file
void SDL_Wrapper::syncFPS() {
    this -> frame++;
    if((this -> fpsLimiter.get_ticks() < 1000/frame_rate))
    {
        SDL_Delay((1000/frame_rate)-fpsLimiter.get_ticks());
        if (this -> debug)
            std::cout << "delaying for " << (1000/frame_rate)- fpsLimiter.get_ticks() << " ms" << std::endl;
    }
    if (this -> refreshScreen) {
        SDL_RenderPresent(this -> mainRenderer);
        this -> refreshScreen = false;
    }
}


// Loads an image from path and returns surface
SDL_Surface* SDL_Wrapper::loadImage(const char* path) {
    SDL_Surface* imageSurface = IMG_Load(path);
    if (imageSurface == NULL) {
        std::cout << "Something went wrong loading your image." << std::endl;
        if (this -> debug)
            printf("%s\n", SDL_GetError());
    }
    
    return imageSurface;
}

// Quits and closes libraries
int SDL_Wrapper::teardown(){
    IMG_Quit();
    SDL_DestroyWindow(this->mainWindow);
    SDL_Quit();
    TTF_Quit();
    //SDLNet_TCP_Close(this -> Server_socket);
    SDLNet_FreeSocketSet(this -> socket);
    SDLNet_Quit();
    SDL_DestroyRenderer(this -> mainRenderer);
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
