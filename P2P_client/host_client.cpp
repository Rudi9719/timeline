#include<iostream>
#include<SDL.h>
#include<SDL_net.h>
#include<string>
#include<fstream>  
#include<ctime>
#include<cstring>

#define MAXLEN 1024

using namespace std;

void timeout(TCPsocket Sending_sock, bool * running, int *timeout){
	while (running)
	{
		*timeout++;
		SDL_Delay(1000);
		if (*timeout == 3) {
			int sent = SDLNet_TCP_Send(Sending_sock, "timeout", 8);
			if (sent < 7) {
				*running = false;
				cout << "timed out" << endl;
			}
		}
		if (*timeout > 60) {
			*running = false;
		}

	}

}

void input(string username, TCPsocket Sending_sock, bool * running ){
	string msg;
	
	string sending_msg;
	while (*running)
	{
	getline(cin, msg);
		if (strcmp(msg.c_str(), "quit") == 0) {
			*running = false;
		}
		
		sending_msg = username;
		sending_msg.append(":");
		sending_msg.append(msg);
		SDLNet_TCP_Send(Sending_sock, sending_msg.c_str(), sending_msg.length() + 1);
		
	}
	
}

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	char temp_char[MAXLEN];
	string msg;
	string host;
	string username;
	string current_user;
	string user_msg;
	IPaddress Host;
	IPaddress Connetion;
	bool started;
	bool starting = true;
	bool running = true;
	int player_num;
	int timeout = 0;
	TCPsocket Listening_sock;
	TCPsocket Player_con_sock;
	TCPsocket Sending_sock;
	SDLNet_SocketSet sock = SDLNet_AllocSocketSet(1);
	
	SDLNet_ResolveHost(&Host, NULL,2560);
	Listening_sock = SDLNet_TCP_Open(&Host);
	
	cout << "Please enter a username without spaces:\n";
	cin >> username;
	cout << "Welcome:" << username << endl;
	cout << "What is your player number";
	cin >> player_num;
	cout << "Please enter Connections IP:" << endl;
	getline(cin, host);
	if (player_num == 1) {
		//start threading here
	}
	
	if (SDLNet_ResolveHost(&Connetion, host.c_str(), 2560) == -1) {
		running = false;
		cout << "There was an error please restart\n";
	}
	Sending_sock = SDLNet_TCP_Open(&Connetion);
	if (!Sending_sock) {
		running = false;
		cout << "There was an error with Socket opening please restart\n";
	}
	//Waiting for players to connect
	while (starting) {
		if (Player_con_sock = SDLNet_TCP_Accept(Listening_sock)) {
			SDLNet_TCP_AddSocket(sock, Player_con_sock);
			starting = false;
		}
	}
	//Start the sendding 
	
	while (running)
	{
		
		
		while (SDLNet_CheckSockets(sock, 0) > 0) {
			if (SDLNet_SocketReady(Player_con_sock)) {
				SDLNet_TCP_Recv(Player_con_sock, temp_char, MAXLEN);
				msg = string(temp_char);
				timeout = 0;
				current_user = msg.substr(0, msg.find(":"));
				user_msg = msg.substr(msg.find(":") + 1, msg.length());
				if (current_user.compare(username) == 0) {
					if (user_msg.compare("quit") == 0) {
						bool running = false;
					}
				}
				else if (user_msg.compare("quit") == 0) {
					running = false;
					cout << msg << endl;
					SDLNet_TCP_Send(Sending_sock, temp_char, MAXLEN);
				}
				else {
					cout << msg << endl;
					SDLNet_TCP_Send(Sending_sock, temp_char, MAXLEN);

				}
			}
		}
	}

	SDLNet_TCP_Close(Listening_sock);
	SDLNet_TCP_Close(Player_con_sock);
	SDLNet_TCP_Close(Sending_sock);
	SDLNet_FreeSocketSet(sock);
	SDL_Quit();
	SDLNet_Quit();
	return 0;
}
