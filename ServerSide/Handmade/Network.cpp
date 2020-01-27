#include "Network.h"

Network::Network()
{
}

Network::~Network()
{
}

bool Network::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 1)
	{
		std::cout << "Error initializing SDL\n";

		system("pause");

		return false;
	}

	if (SDLNet_Init() == -1)
	{
		std::cout << "Error initializing SDL Net\n";

		system("pause");

		return false;
	}

	return true;
}

bool Network::ResolveHost(int port)
{
	if (SDLNet_ResolveHost(&m_IP, nullptr, port) == -1)
	{
		std::cout << "Error creating server IP" << std::endl;

		system("pause");

		return false;
	}

	return true;
}

void Network::Shutdown()
{
	SDLNet_TCP_Close(m_listenSocket);

	SDLNet_Quit();
	SDL_Quit();
}

void Network::WaitForClients()
{
	// nothing for now
}
