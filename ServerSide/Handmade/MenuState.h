#ifndef MENU_STATE_H
#define MENU_STATE_H

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

#include "Background.h"
#include "GameState.h"
#include "MainMenu.h"

class MenuState : public GameState
{
public:

	enum MenuOption { PLAY, QUIT };

public:

	MenuState(GameState* state);
	virtual ~MenuState() {}

public:

	virtual bool OnEnter();
	virtual bool Update();
	virtual bool Draw();
	virtual void OnExit();

private:

	MainMenu* m_menu;
	Background* m_image;
};

#endif