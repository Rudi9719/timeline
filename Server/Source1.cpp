/*
Setting up SDL and SDL_net
*/
#include<iostream>
#include<SDL.h>
#include<SDL_net.h>
#include<string>  
#include<ctime>
#include<cstring>

//Defining Max lenght of string that Client can send to the server
#define MAXLEN 1024

using namespace std;
int main(int argc, char **argv) {
	//TODO : Initialize SDL_net library
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

	
	char temp_char[MAXLEN];
	int activity;
	int Clients = 0;
	IPaddress IP;
	SDLNet_SocketSet socket = SDLNet_AllocSocketSet(5);
	TCPsocket Server_socket;
	TCPsocket client_sock[5];
	//IPaddress *Client_IP;
	bool Running = true;
	
	
	SDLNet_ResolveHost(&IP, NULL, 2560);
	
	Server_socket = SDLNet_TCP_Open(&IP);

	do {
		TCPsocket temp = SDLNet_TCP_Accept(Server_socket);
		
		if (client_sock) {
			if (Clients <= 5) {
				SDLNet_TCP_AddSocket(socket, temp);
				client_sock[Clients] = temp;
				Clients++;
				SDLNet_TCP_Send(temp, "Welcome", 7);
				cout << "New Connections \n";
			}
			else
			{
				SDLNet_TCP_Send(temp, "No_room", 8);
				SDLNet_TCP_Close(temp);
			}

		}
		//Check Data
		while (SDLNet_CheckSockets(socket, 0) > 0) {
			for (int i = 0; i < Clients; i++) {
				if (SDLNet_SocketReady(client_sock[i])) {
					SDLNet_TCP_Recv(client_sock[i], temp_char, MAXLEN);
					
					if (strcmp(temp_char, "quit") || strcmp(temp_char,"shutdown")) {
					// delete socket of client and open it up to new client
						if (strcmp(temp_char, "shutdown")) {
							Running == false;
						}
					}
					else
					{
						for (int k = 0; k < Clients; k++) {
							if (k != i) {
								SDLNet_TCP_Send(client_sock[k], temp_char, strlen(temp_char) + 1);
							}
						}
					}
				}
			}

		}


	} while (Running);
	cout << "server is closeing" << endl;

	SDLNet_TCP_Close(Server_socket);
	SDL_Quit();
	SDLNet_Quit();
	return (0);

}