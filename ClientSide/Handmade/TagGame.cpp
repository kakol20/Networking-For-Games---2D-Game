#include "TagGame.h"

TagGame::TagGame()
{
}

TagGame::~TagGame()
{
}

bool TagGame::Init()
{
	std::cout << "Initializing SDL\n";
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Error initializing SDL\n";

		//system("pause");

		return false;
	}

	std::cout << "Initializing SDL Net\n";
	if (SDLNet_Init() == -1)
	{
		std::cout << "Error initializing SDL Net\n";

		//system("pause");

		return false;
	}

	if (!ResolveHost()) return false;

	if (!OpenSocket()) return false;

	m_exit = false;

	// receive game info
	std::thread t1 = std::thread(&TagGame::ReceiveInfo, this);
	t1.detach();

	return true;
}

void TagGame::Update()
{
	m_player.Update();

	// send info
	std::thread t2 = std::thread(&TagGame::SendInfo, this);

	if (t2.joinable())
	{
		t2.join();
	}

	for (auto it = m_enemyInfo.begin(); it != m_enemyInfo.end(); it++)
	{
		Sphere playerSphere;
		Sphere enemy;

		playerSphere.SetRadius(15);
		enemy.SetRadius(15);

		playerSphere.SetPosition(m_player.GetPosition().x, m_player.GetPosition().y);

		// x-pos$y-pos$score$isTagged

		char sep[] = "$";

		char* x;
		char* y;
		char* score;
		char* tagged;
		char* next;

		int xInt;
		int yInt;

		char* infoConst = (*it).GetString();

		x = strtok_s(infoConst, sep, &next);
		y = strtok_s(NULL, sep, &next);
		score = strtok_s(NULL, sep, &next);
		tagged = strtok_s(NULL, sep, &next);

		std::stringstream xStr;
		xStr << x;
		xStr >> xInt;

		std::stringstream yStr;
		yStr << y;
		yStr >> yInt;

		String taggedStr = tagged;

		if (taggedStr == "true")
		{
			enemy.SetPosition(xInt, yInt);

			if (playerSphere.IsColliding(enemy))
			{
				m_player.SetTagged(false);
			}
		}
	}
}

void TagGame::Draw()
{
	m_player.Draw();
}

bool TagGame::IsDisconnecting()
{
	return false;
}

bool TagGame::OpenSocket()
{
	std::cout << "Opening Socket\n";
	m_socket = SDLNet_TCP_Open(&m_IP);

	if (!m_socket)
	{
		std::cout << "Error opening socket connection" << std::endl;

		//system("pause");

		return false;
	}

	return true;
}

bool TagGame::ResolveHost()
{
	std::cout << "Resolving host\n";
	if (SDLNet_ResolveHost(&m_IP, "localhost", 128) == -1)
	{
		std::cout << "Error resolving host" << std::endl;

		//system("pause");

		return false;
	}

	return true;
}

void TagGame::ReceiveInfo()
{
	while (!m_exit)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		char response[2048] = { '\0' };

		m_enemyInfo.clear();

		//m_player.SetTagged(true);

		if (SDLNet_TCP_Recv(m_socket, response, 2048) <= 0)
		{
			std::cout << "Error recieving message" << std::endl;
		}
		else
		{
			String messageStr = response;

			// info separator per other player: /

			if (messageStr != "none")
			{
				bool isFirst = true;
				char* next;
				char sep[] = "/";

				String nextStr = "_";

				while (nextStr != "")
				{
					char* info;

					if (isFirst)
					{
						info = strtok_s(response, sep, &next);

						String infoStr = info;
						m_enemyInfo.push_back(infoStr);

						isFirst = false;
					}
					else
					{
						info = strtok_s(NULL, sep, &next);

						String infoStr = info;
						m_enemyInfo.push_back(infoStr);
					}

					nextStr = next;
				};
			}
			else
			{
				m_player.SetTagged(true);
			}
		}
	}
}

void TagGame::SendInfo()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	std::stringstream xStrs;
	char x[255] = { '\0' };
	char y[255] = { '\0' };

	xStrs << m_player.GetPosition().x;
	xStrs >> x;

	std::stringstream yStrs;
	yStrs << m_player.GetPosition().y;
	yStrs >> y;

	// x-pos$y-pos$score$isTagged

	String info = x;
	info += "$";
	info += y;
	info += "$0$";

	if (m_player.IsTagged())
	{
		info += "true";
	}
	else
	{
		info += "false";
	}

	if (m_exit)
	{
		info = "exit";
	}

	int length = info.Length() + 1;
	if (SDLNet_TCP_Send(m_socket, info.GetString(), length) < length)
	{
		std::cout << "Error sending message to server " << std::endl;

		m_exit = true;
	}
}