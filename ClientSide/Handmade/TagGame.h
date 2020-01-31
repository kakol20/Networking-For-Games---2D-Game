#ifndef TAGGAME_H
#define TAGGAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <sstream>
#include <thread>
#include <vector>
#include <mutex>

#include "Sprite.h"
#include "String.h"
#include "Text.h"
#include "Player.h"

class TagGame
{
public:
	TagGame();
	~TagGame();

	bool Init();

	void Update();
	void Draw();

	bool IsDisconnecting();

private:
	bool OpenSocket();
	bool ResolveHost();

	void ReceiveInfo();
	void SendInfo();

private:
	IPaddress m_IP;
	TCPsocket m_socket = nullptr;

	bool m_exit;

	Player m_player;

	std::vector<String> m_enemyInfo;
	std::mutex m_mutex;
};

#endif // !TAGGAME_H
