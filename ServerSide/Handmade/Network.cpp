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

bool Network::Start()
{
	m_clients[m_clientIDCount] = new Client(m_clientIDCount);

	std::thread t1 = std::thread(&Network::WaitForClients, this);
	t1.detach();

	// wait for first client to connect
	while (m_clientIDCount <= 0);

	return true; // first client successfully connected

	//return false;
}

void Network::Run()
{
	while (!m_exit)
	{
		// Sending and receiving

		for (auto it = m_clients.begin(); it != m_clients.end(); it++)
		{
			if (!it->second->InThread() && it->second->ClientConnected()) // check if the client's UpdateGame is already in a thread and it's connected
			{
				std::thread t1 = std::thread(&Network::UpdateGame, this, it->first);
				t1.detach();

				it->second->SetInThread(true);
			}
		}

		// Looks for a disconnected client and removes it from map container
		std::vector<int> disconnectedClients; // stores the id of disconnected clients

		for (auto it = m_clients.begin(); it != m_clients.end(); it++)
		{
			if (it->second->IsDisconnecting()) disconnectedClients.push_back(it->first);
		}

		for (auto it = disconnectedClients.begin(); it != disconnectedClients.end(); it++)
		{
			m_clients[(*it)]->CloseSocket();
			delete m_clients[(*it)];
			m_clients[(*it)] = nullptr;

			m_clients.erase((*it));
		}
	}

	Shutdown();

	//return true;
}

void Network::Shutdown()
{
	SDLNet_TCP_Close(m_listenSocket);

	SDLNet_Quit();
	SDL_Quit();
}

void Network::UpdateGame(const int clientID)
{
	while (!m_clients[clientID]->IsDisconnecting()) // does not run code if client is disconnecting or has already disconnected
	{
		// recieves info
		m_clients[clientID]->UpdateInfo();

		if (!m_clients[clientID]->IsDisconnecting()) // checks if client is not disconnecting
		{
			// sends info about other clients to current client
			// info separator per other player: -
			String gameInfo;

			std::lock_guard<std::mutex> lock(m_mutex);
			for (auto it = m_clients.begin(); it != m_clients.end(); it++)
			{
				if (it->first != clientID)
				{
					if (it->second->ClientConnected())
					{
						gameInfo += it->second->GetInfo() + "-";
					}
				}
			}

			// sends info to current client

			m_clients[clientID]->SendText(gameInfo);
		}
		else
		{
			break;
		}
	}
}

void Network::WaitForClients()
{
	while (!m_exit)
	{
		if (m_clients[m_clientIDCount] != nullptr)
		{
			while (m_clients[m_clientIDCount] != nullptr && m_clients[m_clientIDCount]->GetSocket() == nullptr)
			{
				m_clients[m_clientIDCount]->ListenForClient(m_listenSocket);
			}

			if (!m_exit)
			{
				m_clientIDCount++;

				m_clients[m_clientIDCount] = new Client(m_clientIDCount);
			}
		}
	}
}