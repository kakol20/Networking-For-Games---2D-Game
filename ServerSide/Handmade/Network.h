#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <SDL.h>
#include <SDL_net.h>

class Network
{
public:
	Network();
	~Network();

public:
	bool Init();
	bool ResolveHost(int port);
	void Shutdown();
	void WaitForClients();

private:

	IPaddress m_IP;
	TCPsocket m_listenSocket;
};

#endif // !NETWORK_H
