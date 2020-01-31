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
	void Run();
	void Shutdown();

	void UpdateGame(const int clientID);
	void WaitForClients();

	void SetExit(bool flag);
	int GetClientCount();

private:

	IPaddress m_IP;
	TCPsocket m_listenSocket = nullptr;

	bool m_exit = false;
	int m_clientIDCount = 0;
	std::map<int, Client*> m_clients;
	std::mutex m_mutex;
	int m_clientsConnected = 0;
};

#endif // !NETWORK_H
