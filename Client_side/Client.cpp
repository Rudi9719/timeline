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

void ReadMSG(TCPsocket sock, int & quit){

	char msg[MAXLEN];

	while (quit == 0)
		{
		SDLNet_TCP_Recv(sock, msg, MAXLEN);
		cout << msg << endl;
		}
	cout << "Quiting thread now" << endl;
	
}


int main(int argc, char **argv) {
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	
	const char*	IP;
	int Len;
	int quit = 0;
	int Port_input;
	IPaddress Server_IP;
	string IP_input;
	TCPsocket tcpsock;
	string Message;
	
	
	cout << "Please Enter IP or WebAddress";
	cin >> IP_input;
	IP = IP_input.c_str();
	cout << "\n PLease Enter Port Number:";
	cin >> Port_input;
	SDLNet_ResolveHost(&Server_IP, IP, Port_input);
	cout << "\n If you would like to quit please type quit at any time";

	tcpsock = SDLNet_TCP_Open(&Server_IP);
	
	//Add threading here
	thread	Readthread ( ReadMSG , tcpsock, ref(quit));
 	
	//While loop to get user input and send a tcp packet to the server.
	
	while (quit == 0)
	{
		cin >> Message;
		if (Message == "quit") {
			quit = 1;
			//need to end thread with this as well
			
		}
		else {
			Len = Message.size() + 1;
			SDLNet_TCP_Send(tcpsock, Message.c_str(), Len);
		}
	}

	cout << "\n Now leaving the client";
	SDLNet_TCP_Close(tcpsock);
	SDLNet_Quit();
	SDL_Quit();


	return (0);
}
