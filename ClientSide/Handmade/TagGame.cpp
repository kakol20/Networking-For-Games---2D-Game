#include "TagGame.h"
#include "TextureManager.h"

TagGame::TagGame()
{
}

TagGame::~TagGame()
{
}

bool TagGame::Init()
{
	std::cout << "Initializing SDL\n";
	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Enemy.png", "EnemySprite");
	TheTexture::Instance()->LoadFontFromFile("Assets/Fonts/Formula1-Regular.ttf", 100, "MainFont");

	m_enemy.SetTexture("EnemySprite");
	m_enemy.SetSpriteDimension(30, 30);
	m_enemy.SetTextureDimension(1, 1, 30, 30);

	m_enemyTag.SetFont("T");
	m_enemyTag.SetSize(15, 30);

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

	// send info
	std::thread t2 = std::thread(&TagGame::SendInfo, this);
	t2.detach();

	return true;
}

void TagGame::Update()
{
	if (!m_enemyInfo.empty())
	{
		for (auto it = m_enemyInfo.begin(); it != m_enemyInfo.end(); it++)
		{
			char* next;

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
	else
	{
		m_player.SetTagged(true);
	}

	m_player.Update();
}

void TagGame::Draw()
{
	m_player.Draw();

	for (auto it = m_enemyInfo.begin(); it != m_enemyInfo.end(); it++)
	{
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

		m_enemy.Draw(xInt - 15, yInt - 15);

		if (taggedStr == "true")
		{
			m_enemyTag.Draw(xInt - 7, yInt - 15);
		}
	}
}

bool TagGame::IsDisconnecting()
{
	return false;
}

void TagGame::SetExit(const bool flag)
{
	m_exit = flag;
}

void TagGame::CloseSocket()
{
	SDLNet_TCP_Close(m_socket);
}

void TagGame::Shutdown()
{
	SDLNet_Quit();
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

		//m_player.SetTagged(true);
		m_enemyInfo.clear();

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

				char* next;
				char sep[] = "/";

				char* enemyCount;
				
				enemyCount = strtok_s(response, sep, &next);

				// convert enemy count to int

				int enemyCountInt;
				std::stringstream eStr;
				eStr << enemyCount;
				eStr >> enemyCountInt;

				for (int i = 0; i < enemyCountInt; i++)
				{
					char* info;

					info = strtok_s(NULL, sep, &next);

					m_enemyInfo.push_back(info);
				}

				/*String nextStr = "_";

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
				};*/
			}
		}
	}
}

void TagGame::SendInfo()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	while (!m_exit)
	{
		std::stringstream xStrs;
		char x[255] = { '\0' };
		char y[255] = { '\0' };
		char score[255] = { '\0' };

		xStrs << m_player.GetPosition().x;
		xStrs >> x;

		std::stringstream yStrs;
		yStrs << m_player.GetPosition().y;
		yStrs >> y;

		std::stringstream scoreStr;
		scoreStr << m_player.GetScore();
		scoreStr >> score;

		// x-pos$y-pos$score$isTagged

		String info = x;
		info += "$";
		info += y;
		info += "$";
		info += score;
		info += "$";

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
}