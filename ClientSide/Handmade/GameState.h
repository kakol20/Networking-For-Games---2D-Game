#ifndef GAME_STATE_H
#define GAME_STATE_H

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
| 'GameState' source files last updated in June 2019 									        |
#==============================================================================================*/

class GameState
{

public:
	
	GameState(GameState* state);
	virtual ~GameState() = 0 {}

public:

	bool& IsAlive();
	bool& IsActive();

public:

	virtual bool OnEnter() = 0;
	virtual bool Update() = 0;
	virtual bool Draw() = 0;
	virtual void OnExit() = 0;

protected:

	bool m_isAlive;
	bool m_isActive;
	GameState* m_previousState;

};

#endif