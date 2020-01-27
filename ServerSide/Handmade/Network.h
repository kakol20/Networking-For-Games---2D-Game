#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <map>
#include <mutex>
#include <SDL.h>
#include <SDL_net.h>
#include <thread>
#include <vector>

#include "Client.h"
#include "String.h"

class Network
{
public:
	Network();
	~Network();

public:
	bool Init();
	bool ResolveHost(int port);

	bool Start();
	bool Run();
	void Shutdown();

	void UpdateGame(const int clientID);
	void WaitForClients();

private:

	IPaddress m_IP;
	TCPsocket m_listenSocket;

	bool m_exit = false;
	int m_clientIDCount = 0;
	std::map<int, Client*> m_clients;
	std::mutex m_mutex;
};

#endif // !NETWORK_H
