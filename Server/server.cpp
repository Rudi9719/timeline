//TODO Time out on here you will send
//TODO threading for all of this and checking for the time out
/*
Setting up SDL and SDL_net
*/
#include<iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include<string>  
#include<ctime>
#include<cstring>

//Defining Max lenght of string that Client can send to the server
#define MAXLEN 1024
using namespace std;
typedef struct {
	int * timeout;
	bool * running;
} ThreadData;

//Time out function:Send timeout to all clients every 3 seconds if error quit
int Timeout( void* data) {
	ThreadData *tdata = (ThreadData*)data;
	int *timeout = tdata->timeout;
	bool *running = tdata->running;
	free(data);
	while (*running) {
		SDL_Delay(1000);
			*timeout++;
		if (*timeout >= 10) {
			*running = false;
		}
	}
			return 0;
}



int main(int argc, char **argv) {
	// Initialize SDL_net library
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

	//All the varible that this code needs
	char temp_char[MAXLEN];
	string temp_string;
	int timeout = 0;
	int Clients = 0;
	int players;
	int threadReturnValue;
	IPaddress IP;
	
	/*
	allocate the socket set as well as creating a socket set
	*/

	SDLNet_SocketSet socket = SDLNet_AllocSocketSet(5);
	TCPsocket Server_socket;
	TCPsocket client_sock[5];
	//IPaddress *Client_IP;
	bool Running = true;
	
	//Setup the server to be listening on port 2560
	SDLNet_ResolveHost(&IP, NULL, 2560);
	
	Server_socket = SDLNet_TCP_Open(&IP);
	
	cout << "Started" << endl;
	cout << "Please enter number of players between 2 and 5" << endl;
	cin >> players;
	while (players > 5 || players < 2) {
		cout << "Please enter number of players between 2 and 5" << endl;
		cin >> players;
	}
	ThreadData *data = (ThreadData*)malloc(sizeof(ThreadData));
	data->running = &Running;
	data->timeout = &timeout;
	
	
	while (Clients < players) {
		TCPsocket temp = SDLNet_TCP_Accept(Server_socket);

		if (temp) {
			//checks to see if there is room for clients, if so add, else close there socket
			if (Clients <= 5) {
				cout << "here" << endl;
				SDLNet_TCP_AddSocket(socket, temp);
				client_sock[Clients] = temp;
				cout << "here" << endl;
				Clients++;
				cout << "here" << endl;
				temp_string = to_string(Clients);
				SDLNet_TCP_Send(temp, temp_string.c_str(), MAXLEN + 1);
				if (Clients == 0) {
					while (SDLNet_CheckSockets(socket, 0) > 0) {
						if (SDLNet_SocketReady(client_sock[0])) {
							SDLNet_TCP_Recv(client_sock[0], temp_char, MAXLEN);
							//grab card vector here for Card deck
						}
					}
				}
			}
			else
			{
				SDLNet_TCP_Send(temp, "No_room", 9);
				SDLNet_TCP_Close(temp);
			}

		}
	}
	SDL_Thread * mythread = SDL_CreateThread(Timeout,"TImeout", data);
	do {
		//Check Data
		while (SDLNet_CheckSockets(socket, 0) > 0) {
			for (int i = 0; i < Clients; i++) {
				if (SDLNet_SocketReady(client_sock[i])) {
					SDLNet_TCP_Recv(client_sock[i], temp_char, MAXLEN);
					cout << temp_char << endl;
					
					if (strcmp(temp_char, "quit") ==0 || strcmp(temp_char,"shutdown") == 0) {
					// delete socket of client and open it up to new client

							Running = false;
						
					}
					else
					{
						//send all data recieve from client I to all clients except I
						for (int k = 0; k < Clients; k++) {
							if (k != i) {
								int result = SDLNet_TCP_Send(client_sock[k], temp_char, strlen(temp_char) + 1);
								if (result < strlen(temp_char)) {
									Running = false;
								}
								else
								{
									timeout = 0;
								}
								
							}
						//After send the data, Send a signal to the next person to go
							if (i == Clients) {
								SDLNet_TCP_Send(client_sock[0], "YT", 3);
							}
							else {
								SDLNet_TCP_Send(client_sock[i + 1], "YT", 3);
							}
						}
					}
				}
			}

		}
		if (timeout >= 5) {
			for (int k = 0; k < Clients; k++) {
					int result = SDLNet_TCP_Send(client_sock[k], "timeout", 8);
					if (result < 7) {
						Running = false;
					}
				}
			timeout = 0;
		}


	} while (Running);
	SDL_WaitThread(mythread, &threadReturnValue);
	cin >> Clients;
	cout << "server is closeing" << endl;
	//De deinitialize everything
	SDLNet_TCP_Close(Server_socket);
	SDLNet_FreeSocketSet(socket);
	SDL_Quit();
	SDLNet_Quit();
	return (0);

}
