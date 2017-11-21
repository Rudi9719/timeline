#include<iostream>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_net.h>
#include<string>
#include<thread> 
#include<ctime>
#include<string>
#include<sstream>

#define MAXLEN 1024

using namespace std;
//Counting timeout
int Timeout(bool * running, int* timeout) {
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

//Cin thread
int Sending() {
	return 0;
}


int main(int argc, char **argv) {
	//This to:
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	SDLNet_SocketSet Client_set = SDLNet_AllocSocketSet(1);
	char Msg[MAXLEN];
	//	const char*	IP;
	int Player;
	int can_send = 1;
	int Len;
	int quit = 0;
	int timeout = 0;
	//	int Port_input;
	IPaddress Server_IP;
	string IP_input;
	TCPsocket tcpsock;
	string Message;
	//This implement

	/*cout << "Please Enter IP or WebAddress:   ";
	getline(cin, IP_input);
	SDLNet_ResolveHost(&Server_IP, "localhost", 2560);
	cout << "\n If you would like to quit please type quit at any time \n";

	tcpsock = SDLNet_TCP_Open(&Server_IP);
	*/

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

	while (quit == 0)
	{
		if (can_send == 0) {


			can_send = 1;
			if (Message == "quit") {
				Len = Message.size() + 1;
				SDLNet_TCP_Send(tcpsock, Message.c_str(), Len);
				quit = 1;
				//need to end thread with this as well

			}
			else {
				Len = Message.size() + 1;
				SDLNet_TCP_Send(tcpsock, Message.c_str(), Len);
				cout << "sent \n";
			}
		}
		// checks and recieves and data
		if (SDLNet_CheckSockets(Client_set, 0) > 0 && SDLNet_SocketReady(tcpsock)) {
			SDLNet_TCP_Recv(tcpsock, Msg, MAXLEN);
			cout << Msg;
			if (strcmp(Msg, "YT") == 0){
			can_send = 0;
			}
			if (strcmp(Msg, "quit")== 0) {
				quit = 1;
			}

			
		}
	}
	
	cout << "\n Now leaving the client";
	SDLNet_TCP_Close(tcpsock);
	SDLNet_FreeSocketSet(Client_set);
	SDLNet_Quit();
	SDL_Quit();

	cin >> quit;



	return (0);
}