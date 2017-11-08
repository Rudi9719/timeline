//
//  SDL_Wrapper.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "SDL_Wrapper.hpp"
#include <cstring>


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
        SDLNet_Init();
        this -> mainRenderer = SDL_CreateRenderer(this -> mainWindow, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor(this -> mainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(this -> mainRenderer);
        SDL_RenderPresent(this -> mainRenderer);
    }
    Card* helpCard = this -> renderCard(width-80, 0);
    placedCards.back().setCardType(9);
    this -> colorizeCard(helpCard, 255,100,100);
    this -> displayText("Help", width - 60, 10, 30);
    this -> startFPS();
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
    this -> refreshScreen = true;

    if (this -> debug)
        printf("Error: %s\n", SDL_GetError());

}
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
void SDL_Wrapper::handleClick(int x, int y) {
    std::cout << "Mouse Event:" << std::endl;
    std::cout << "X: " << x << " Y: " << y << std::endl;
    for(Card card : placedCards) {
        std::cout << card.getCardType() << " ";
        if (card.cardButton.ownsClick(x, y, card.cardRect)) {
            card.handleClick(x, y);
            return;
        }
    }
    std::cout << "" << std::endl;

    cardPlacer(x,y);

    std::cout << "Card vector column values:" << std::endl;
    for (int i = 0;i<placedCards.size();i++) {
        std::cout << placedCards.at(i).getColumn() << " ";
    }
}

void SDL_Wrapper::cardPlacer(int mousex, int mousey) {

        int column_selected =-1;
        int cardy = 0;

        if((mousex>((this->width/2)-(card_width*2.5)))&&(mousex<((this->width/2)-(card_width*1.5)))) {
           column_selected =1;
        }
        else if ((mousex>((this->width/2)-(card_width*1.5)))&&(mousex<((this->width/2)-(card_width*0.5)))) {
            column_selected = 2;
        }
        else if ((mousex>((this->width/2)-(card_width*0.5)))&&(mousex<((this->width/2)+(card_width*0.5)))) {
            column_selected = 3;
        }
        else if ((mousex>((this->width/2)+(card_width*0.5)))&&(mousex<((this->width/2)+(card_width*1.5)))) {
            column_selected = 4;
        }
        else if ((mousex>((this->width/2)+(card_width*1.5)))&&(mousex<((this->width/2)+(card_width*2.5)))) {
            column_selected = 5;
        }
        std::cout << "Column " << column_selected << " Selected" << std::endl;
        int cardsincolumn = 0;

        for(int i=0;i<placedCards.size();i++) {
            if (placedCards.at(i).getColumn()==column_selected)
                cardsincolumn++;
        }

        if (cardsincolumn ==0)
            cardy = ((this->height/2)-(card_height/2));

        int highY;
        int lowY;

        if (!(cardsincolumn==0)) {

            //Initialize high and low Y
            for(int i = 0; i<placedCards.size();i++) {
                if(placedCards.at(i).getColumn() == column_selected) {
                    lowY = placedCards.at(i).getY();
                    highY = placedCards.at(i).getY();
                    break;
                }
            }

            // Find current high and low Y values
            for(int i =0; i<placedCards.size();i++) {
                if((placedCards.at(i).getColumn()==column_selected)&&(placedCards.at(i).getY()>highY)) {
                    highY = placedCards.at(i).getY();
                }
                if((placedCards.at(i).getColumn()==column_selected)&&(placedCards.at(i).getY()<lowY)) {
                    lowY = placedCards.at(i).getY();
                }
            }

            // Modify Y to match user's demands
            if (mousey<(this->height)/2) { //lower than middle screen
                cardy = lowY-100;
            }
            else if (mousey>(this->height)/2) { //higher than middle screen
                cardy = highY+100;
            }
        }
        if (column_selected != -1) {
            Card* newCard = renderCard((((this->width/2)-(card_width*2.5))+((column_selected-1)*card_width)), cardy);
            placedCards.back().setColumn(column_selected);
            placedCards.back().setCardType(0);
            //CALL FUNCTION TO SHIFT CARDS HERE
            shiftCardColumn(column_selected);
            clearScreen(0,0,0,255);
            displayCards();
        }
}

Card* SDL_Wrapper::renderCard(int x, int y) {
    SDL_ClearError();

    SDL_Rect r1;
    int cardRGBgrey = 200;
    cardRGBgrey = cardRGBgrey - (((this->placedCards.size())*10)%200);
    r1.x = x;
    r1.y = y;
    r1.w = card_width;
    r1.h = card_height;
    Card c = Card(r1);
    // Wipe screen clear and get ready to display next frame of cards
    clearScreen(cardRGBgrey,cardRGBgrey,cardRGBgrey,255);
    SDL_SetRenderDrawColor( this -> mainRenderer, cardRGBgrey,cardRGBgrey,cardRGBgrey,255);
    if (this -> debug)
        printf("%s\n", SDL_GetError());
    c.setRGB
    (
        c.getR()-(((this->placedCards.size())*10)%170),
        c.getG()-(((this->placedCards.size())*10)%170),
        c.getB()-(((this->placedCards.size())*10)%170)
    );
    this -> refreshScreen = true;
    this -> placedCards.push_back(c);
    Card* ret = &placedCards.back();
    return ret;

}

void SDL_Wrapper::displayCards() {
    //goes through all placed cards
    for(int i = 0;i<placedCards.size();i++) {
        //adds cards to frame to be displayed
        /*SDL_SetRenderDrawColor(this -> mainRenderer,
                               placedCards.at(i).getR(),
                               placedCards.at(i).getG(),
                               placedCards.at(i).getB(),
                               255);
        */
        SDL_Surface *img = placedCards.at(i).getCardSurface();
        img = SDL_LoadBMP("assets/testcard.bmp");
        if(img == NULL)
            std::cout << "Error loading testcard BMP" << std::endl;
        SDL_Texture *texture = placedCards.at(i).getCardTexture();
        texture = SDL_CreateTextureFromSurface(this->mainRenderer, img);
        SDL_RenderCopy(this->mainRenderer,texture,NULL,&placedCards.at(i).cardRect);
        //SDL_RenderFillRect(this -> mainRenderer, &placedCards.at(i).cardRect);
    }
}

void SDL_Wrapper::shiftCardColumn(int target_column) {
    for(int i = 0;i<placedCards.size();i++) {
        if (placedCards.at(i).getColumn()==target_column)
            placedCards.at(i).setY(placedCards.at(i).getY()-25);
    }
}

void SDL_Wrapper::clearScreen(int r,int g,int b, int opac) {
    SDL_SetRenderDrawColor(this -> mainRenderer, 0,0,0,255);
    SDL_RenderClear(this -> mainRenderer);
    //uses passed vars to set draw color back to what it was originally
    SDL_SetRenderDrawColor(this -> mainRenderer, r, g, b,opac);
}


void SDL_Wrapper::colorizeCard(SDL_Rect* card, int r, int g , int b) {
    SDL_ClearError();
    SDL_SetRenderDrawColor(this -> mainRenderer, r, g, b, 255 );
    displayCards();
    this -> refreshScreen = true;
}
void SDL_Wrapper::colorizeCard(Card* card, int r, int g , int b) {
    SDL_ClearError();
    SDL_SetRenderDrawColor(this -> mainRenderer, r, g, b, 255 );
    SDL_RenderFillRect(this -> mainRenderer, &card -> cardRect);
    this -> refreshScreen = true;
}
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
void SDL_Wrapper::moveCard(int xTransform, int yTransform, SDL_Rect* card) {
    SDL_ClearError();
    card -> x = (card -> x) - xTransform;
    card -> y = (card -> y) - yTransform;
    this -> refreshScreen = true;
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
    if (this -> refreshScreen) {
        SDL_RenderPresent(this -> mainRenderer);
        this -> refreshScreen = false;
    }
}
void SDL_Wrapper::reDrawCards() {
    for (Card c : placedCards) {
        this -> colorizeCard(&c, 0, 0, 0);
    }
    SDL_RenderPresent(this -> mainRenderer);
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

int SDL_Wrapper::getWindowHeight() {
    return this->height;
}
int SDL_Wrapper::getWindowWidth() {
    return this->width;
}
