//
//  main.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 CS350. All rights reserved.
//

#include <iostream>
#include "Wrappers/SDL_Wrapper.hpp"




int main(int argc, const char * argv[]) {
        bool quit = false;
        SDL_Wrapper wrapper = SDL_Wrapper(900, 1000);
        SDL_Event event;
        while (!quit) {
            wrapper.startFPS();
                while (SDL_PollEvent(&event)) {
                    
                        switch(event.type) {

                        case SDL_QUIT:
                                quit = true;
                                break;

                        case SDL_KEYDOWN:
                                switch (event.key.keysym.sym) {

                                case SDLK_ESCAPE:
                                        quit = true;
                                        break;
                                }
                            case SDLK_SPACE:
                                wrapper.displayText("Yo mother fucker!", 100, 100);
                                break;
                        }

                }
            wrapper.syncFPS();
        }

        return wrapper.quit();
}
