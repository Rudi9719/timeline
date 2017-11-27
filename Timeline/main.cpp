//
//  main.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 CS350. All rights reserved.
//

#include <iostream>
#include "Wrappers/SDL_Wrapper.hpp
#undef main
#define MAXLEN 1024
typedef struct {
	int * timeout;
	int * can_send;
	bool *running;
	TCPsocket * Client_sock;
}ThreadData;

int Timeout(void * data) {
	ThreadData *tdata = (ThreadData*)data;
	int *timeout = tdata->timeout;
	bool *running = tdata->running;
	free(data);
	while (running)
	{
		*timeout++;
		SDL_Delay(1000);
		if (*timeout > 10) {
			*running = false;
		}
	}

	return 0;
}

void Recv(void * data){
	ThreadData *tdata = (ThreadData*)data;
	int *timeout = tdata->timeout;
	int *can_send = tdata->can_send;
	bool *running = tdata->running;
	TCPsocket * Client_sock = tdata->Client_sock;
	char Msg[MAXLEN];
	int x;
	int y;
	while(running){
		if (SDLNet_CheckSockets(Client_set, 0) > 0 && SDLNet_SocketReady(tcpsock)) {
			SDLNet_TCP_Recv(tcpsock, Msg, MAXLEN);
			// Split the string into an x and y
			wrapper.handleClick(x,y);
			if (strcmp(Msg, "YT") == 0){
				can_send = 0;
				}
			if (strcmp(Msg, "quit")== 0) {
				running = false;
				wrapper.quit = true;
				}

			
		}
	}
}
int main(int argc, const char * argv[]);

int WinMain(int argc, const char* argv[]) {
    return main(argc, argv);
}


int main(int argc, const char * argv[]) {
	
	SDLNet_SocketSet Client_set = SDLNet_AllocSocketSet(1);
	char Msg[MAXLEN];
	//	const char*	IP;
	int Player;
	int can_send = 1;
	int Len;
	bool running = true;
	int timeout = 0;
	//	int Port_input;
	IPaddress Server_IP;
	string IP_input;
	TCPsocket tcpsock;
	string Message;
	
	SDLNet_ResolveHost(&Server_IP, "127.0.0.1", 2560);
	tcpsock = SDLNet_TCP_Open(&Server_IP);
	SDLNet_TCP_AddSocket(Client_set, tcpsock);
	cout << "Started" << endl;

	SDLNet_TCP_Recv(tcpsock, Msg, MAXLEN);
	Player = atoi(Msg);
	cout << Msg << "\n";
		if (Msg[0] == '0') {
		can_send = 0;
		//send vector
	}
	ThreadData *data = (ThreadData*)malloc(sizeof(ThreadData));
	data->running = &running;
	data->timeout = &timeout;
	data->Client_sock = &tcpsock;
	data->can_send = &can_send;
        SDL_Wrapper wrapper = SDL_Wrapper(850, 1000);
        SDL_Event event;


	SDL_Thread * mythread1 = SDL_CreateThread(Timeout,"TImeout", data);
	SDL_Thread * mythread2 = SDL_CreateThread(Recv,"Recv", data);
        while (!wrapper.quit) {
                while (SDL_WaitEventTimeout(&event, 4)) {

                        switch(event.type) {

                        case SDL_QUIT:
                                wrapper.quit = true;
								//send a quit 
                                break;

                        case SDL_KEYDOWN:
                                switch (event.key.keysym.sym) {

                                case SDLK_ESCAPE:
                                        wrapper.quit = true;
                                        break;

                                case SDLK_SPACE:
                                        break;

                                } // End switch on key
                                case SDL_MOUSEBUTTONDOWN:
                                        if (event.button.button == SDL_BUTTON_LEFT) {
                                            int x = event.button.x;
                                            int y = event.button.y;
											//add this to string and send
                                            wrapper.handleClick(x, y);

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
