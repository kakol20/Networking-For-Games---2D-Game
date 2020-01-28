#ifndef TAGGAME_H
#define TAGGAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <sstream>
#include <thread>

#include "Sprite.h"
#include "String.h"
#include "Text.h"

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

private:
	IPaddress m_IP;
	TCPsocket m_socket = nullptr;

	bool m_exit;
};

#endif // !TAGGAME_H
