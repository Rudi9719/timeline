//
//  main.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 CS350. All rights reserved.
//
#include <iostream>
#include "Wrappers/SDL_Wrapper.hpp"
#undef main

int main(int argc, const char * argv[]);

int WinMain(int argc, const char* argv[]) {
    return main(argc, argv);
}

int main(int argc, const char * argv[]) {
<<<<<<< HEAD

    SDL_Wrapper wrapper = SDL_Wrapper(850, 1000);
    SDL_Event event;
=======
	int currentPlayer = 0;
        SDL_Wrapper wrapper = SDL_Wrapper(850, 1000);
        SDL_Event event;
        

>>>>>>> master

    while (!wrapper.quit) {
        while (SDL_WaitEventTimeout(&event, 4)) {

            switch (event.type) {

            case SDL_QUIT:
                wrapper.quit = true;
                //send a quit 
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {

                case SDLK_ESCAPE:
                    wrapper.quit = true;
                    break;

<<<<<<< HEAD
                case SDLK_SPACE:
                    break;

                } // End switch on key
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x = event.button.x;
                    int y = event.button.y;
                    wrapper.handleClick(x, y);
=======
                                case SDLK_SPACE:
                                        break;
                                    case SDLK_UP:
                                        wrapper.players[currentPlayer].movePlayer(0, -15);
                                        wrapper.handleMovement(currentPlayer);
                                        break;
                                    case SDLK_DOWN:
                                        wrapper.players[currentPlayer].movePlayer(0, 15);
                                        wrapper.handleMovement(currentPlayer);
                                        break;
                                    case SDLK_LEFT:
                                        wrapper.players[currentPlayer].movePlayer(-15, 0);
                                        wrapper.handleMovement(currentPlayer);
                                        break;
                                    case SDLK_RIGHT:
                                        wrapper.players[currentPlayer].movePlayer(15, 0);
                                        wrapper.handleMovement(currentPlayer);
                                        break;
									case SDLK_RETURN:
										if(currentPlayer == 4){
											currentPlayer=0;
										}else{
											currentPlayer++;
										}
                                } // End switch on key
                                case SDL_MOUSEBUTTONDOWN:
                                        if (event.button.button == SDL_BUTTON_LEFT) {
                                            int x = event.button.x;
                                            int y = event.button.y;
                                            wrapper.handleClick(x, y);
>>>>>>> master

                }
                break;

            } // End switch on event.type

        } // End Poll event loop
        SDL_FlushEvent(event.type);
        wrapper.syncFPS();

    } // End main loop
    std::cout << wrapper.teardown() << std::endl;
    return 0;
}
