#include "TagGame.h"

TagGame::TagGame()
{
}

TagGame::~TagGame()
{
}

bool TagGame::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Error initializing SDL thr\n";

		system("pause");

		return false;
	}

	if (SDLNet_Init() == -1)
	{
		std::cout << "Error initializing SDL Net\n";

		system("pause");

		return false;
	}

	if (!ResolveHost()) return false;

	if (!OpenSocket()) return false;

	m_exit = false;

	return true;
}

void TagGame::Update()
{
	// receive game info


	// send info
}

void TagGame::Draw()
{
}

bool TagGame::IsDisconnecting()
{
	return false;
}

bool TagGame::OpenSocket()
{
	m_socket = SDLNet_TCP_Open(&m_IP);

	if (!m_socket)
	{
		std::cout << "Error opening socket connection" << std::endl;

		system("pause");

		return false;
	}

	return true;
}

bool TagGame::ResolveHost()
{
	if (SDLNet_ResolveHost(&m_IP, "127.0.0.1", 1945) == -1)
	{
		std::cout << "Error resolving host" << std::endl;

		system("pause");

		return false;
	}

	return true;
}
