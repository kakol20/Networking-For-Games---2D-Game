#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

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
| 'GameObject' source files last updated in June 2019 									        |
#==============================================================================================*/

#include <string>
#include <SDL.h>

class GameObject 
{

public:

	GameObject();
	virtual ~GameObject() = 0 {}
	
public:

	bool& IsAlive();
	bool& IsActive();
	bool& IsVisible();

public:

	SDL_Point GetPosition();
	const std::string& GetTag();

	void SetTag(const std::string& tag);
	void SetPosition(int x, int y);

public:

	virtual void Update() = 0;
	virtual bool Draw() = 0;

protected:

	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;

	std::string m_tag;
	SDL_Point m_position;

};

#endif