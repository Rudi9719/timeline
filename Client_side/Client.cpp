#include<iostream>
#include<cstdlib>
#include<SDL.h>
#include<SDL_net.h>
#include<string>
#include<thread> 
#include<ctime>
#include<string>

#define MAXLEN 1024

using namespace std;

/*
Threaded Read MSg
*/

/*void ReadMSG(TCPsocket sock, int &quit){

char msg[MAXLEN];
cout << "in thread";
int result;
while (quit == 0)
	{
	result = SDLNet_TCP_Recv(sock, msg, MAXLEN - 1);
	if (result <= 0) {
		SDLNet_TCP_Close(sock);
		
	}
	else {
		msg[result] = 0;
		cout << msg;
	}

	}
cout << "Quiting thread now" << endl;
}
*/

int main(int argc, char **argv) {
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	SDLNet_SocketSet Client_set = SDLNet_AllocSocketSet(1);
	char Msg[MAXLEN];
//	const char*	IP;
	int can_send = 1;
	int Len;
	int quit = 0;
//	int Port_input;
	IPaddress Server_IP;
	string IP_input;
	TCPsocket tcpsock;
	string Message;
	
	
	/*cout << "Please Enter IP or WebAddress:   ";
	getline(cin, IP_input);
	SDLNet_ResolveHost(&Server_IP, "localhost", 2560);
	cout << "\n If you would like to quit please type quit at any time \n";

	tcpsock = SDLNet_TCP_Open(&Server_IP);
	*/


	SDLNet_ResolveHost(&Server_IP, "127.0.0.1", 2560);
	tcpsock = SDLNet_TCP_Open(&Server_IP);
	SDLNet_TCP_AddSocket(Client_set, tcpsock);

	//Add threading here
	//thread	Readthread ( ReadMSG , tcpsock, ref(quit));
	SDLNet_TCP_Recv(tcpsock, Msg, MAXLEN);
	cout << Msg << "\n";
	if (Msg[0] == '0') {
		can_send = 0;
	}
	while (quit == 0)
	{
		if (can_send == 0) {

			getline(cin, Message);
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
		if (SDLNet_CheckSockets(Client_set,0) > 0 &&  SDLNet_SocketReady(tcpsock)) {
			SDLNet_TCP_Recv(tcpsock, Msg, MAXLEN);
			cout << Msg;
			can_send = 0;
			if (strcmp(Msg, "quit")) {
				quit = 1;
			}

		}
	}

	cout << "\n Now leaving the client";
	SDLNet_TCP_Close(tcpsock);
	SDLNet_FreeSocketSet(Client_set);
	SDLNet_Quit();
	SDL_Quit();

	cin >> quit ; 

	return (0);
}