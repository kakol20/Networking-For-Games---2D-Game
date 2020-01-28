#ifndef GAME_H
#define GAME_H

/*==============================================================================================#
|                                                                                               |
| Copyright (c) 2019 Karsten Vermeulen. All rights reserved.                                    |
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade Lite' game engine,    |
| for the purposes of educating other fellow programmers, programming students and anyone else  |
| wishing to learn about game development, C++ and OOP. The structure of the engine, class      |
| design and overall code is constantly under development.                                      |
|                                                                                               |
| Designed to teach. Made from scratch. Built by hand.  						                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade Lite' and wish to show your support, if you have any questions about    |
| the project, or if you just want to reach out, please find me on the following channels:      |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Game' source files last updated in June 2019 									            |
#==============================================================================================*/

#include <deque>
#include <string>
#include "GameState.h"
#include "Singleton.h"

class Game
{
public:

	friend class Singleton<Game>;

public:

	int GetTotalTime();
	int GetElapsedTime();

public:

	bool Initialize(const std::string& name, int screenWidth,
		int screenHeight, bool fullscreen = false);

	void AddState(GameState* state);
	void ChangeState(GameState* state);

	bool Run();
	void ShutDown();

private:

	Game();
	Game(const Game&);
	Game& operator=(const Game&);

private:

	void RemoveState();

private:

	bool m_endGame;
	int m_elapsedTime;
	std::deque<GameState*> m_gameStates;
};

typedef Singleton<Game> TheGame;

#endif