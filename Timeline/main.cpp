///
//  main.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 CS350. All rights reserved.
//

#include <iostream>
#include "SDL_Wrapper.hpp"
#undef main

int main(int argc, const char * argv[]);

int WinMain(int argc, const char* argv[]) {
	return main(argc, argv);
}


int main(int argc, const char * argv[]) {
	int currentPlayer = 0;
	std::string tmp;
	SDL_Wrapper wrapper = SDL_Wrapper(850, 1000);
	SDL_Event event;
	currentPlayer = wrapper.Your_num;
	


	while (!wrapper.quit) {

		while (SDL_WaitEventTimeout(&event, 4)) {

			switch (event.type) {

			case SDL_QUIT:
				wrapper.quit = true;
				wrapper.sendPacket("quit");
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

				case SDLK_ESCAPE:
					wrapper.quit = true;
					wrapper.sendPacket("quit");
					break;

				case SDLK_SPACE:
					break;
				case SDLK_UP:
				if(wrapper.yourTurn){
					wrapper.players[currentPlayer].movePlayer(0, -15);
					wrapper.handleMovement(currentPlayer);
					tmp = "p," + std::to_string(currentPlayer) + ",0,-15";
					wrapper.sendPacket(tmp);
					}
					break;
				case SDLK_DOWN:
				if(wrapper.yourTurn){
					wrapper.players[currentPlayer].movePlayer(0, 15);
					wrapper.handleMovement(currentPlayer);
					tmp = "p," + std::to_string(currentPlayer) + ",0,15";
					wrapper.sendPacket(tmp);
					}
					break;
				case SDLK_LEFT:
				if(wrapper.yourTurn){				
					wrapper.players[currentPlayer].movePlayer(-15, 0);
					wrapper.handleMovement(currentPlayer);
					tmp = "p," + std::to_string(currentPlayer) + ",-15,0";
					wrapper.sendPacket(tmp);
					}
					break;
				case SDLK_RIGHT:
				if(wrapper.yourTurn){
					wrapper.players[currentPlayer].movePlayer(15, 0);
					wrapper.handleMovement(currentPlayer);
					tmp = "p," + std::to_string(currentPlayer) + ",15,0";
					wrapper.sendPacket(tmp);
					}
					break;
				case SDLK_RETURN:
				if(wrapper.yourTurn){
                    wrapper.yourTurn = false;
					wrapper.sendPacket("YT");
				}
					break;
				} // End switch on key
			case SDL_MOUSEBUTTONDOWN:
				if(wrapper.yourTurn){}
				if (event.button.button == SDL_BUTTON_LEFT) {
					int x = event.button.x;
					int y = event.button.y;
					wrapper.handleClick(x, y);
					tmp = "c," + std::to_string(x) + "," + std::to_string(y);
                    wrapper.sendPacket(tmp);
				}
				break;

			} // End switch on event.type

		} // End Poll event loop
	
		SDL_FlushEvent(event.type);
		wrapper.syncFPS();
		wrapper.receivingThread();

	} // End main loop
	std::cout << wrapper.teardown() << std::endl;
	return 0;
}
